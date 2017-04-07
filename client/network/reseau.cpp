#include "network/reseau.h"
#include "graphicGame/gamefield.h"
#include "entities/character.h"
#include "scenery/data.h"

Reseau::Reseau(Data *data,QObject *parent) :
    QObject(parent)
{
    m_data = data;
    m_socket = new QTcpSocket;
    m_tailleMessage = 0;
    qRegisterMetaType <QAbstractSocket::SocketError>("QAbstractSocket::SocketError");
    connect(m_socket, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(erreurSocket(QAbstractSocket::SocketError)));
    connect(m_socket, SIGNAL(readyRead()), this, SLOT(donneesRecues()));
    m_gameField = 0;
    m_character = 0;
}

Reseau::~Reseau()
{
    delete m_socket;
}

void Reseau::start()
{
    m_socket->connectToHost("127.0.0.1",PORT);
}

void Reseau::erreurSocket(QAbstractSocket::SocketError erreur)
{
    switch(erreur)
    {
        case QAbstractSocket::HostNotFoundError:
            emit erreurReseau(trUtf8("ERREUR : le serveur n'a pas pu être trouvé. Vérifiez l'IP et le port."));
            break;
        case QAbstractSocket::ConnectionRefusedError:
            emit erreurReseau(trUtf8("ERREUR : le serveur a refusé la connexion. Vérifiez si le programme \"serveur\" a bien été lancé. Vérifiez aussi l'IP et le port."));
            break;
        case QAbstractSocket::RemoteHostClosedError:
            emit erreurReseau(trUtf8("ERREUR : le serveur a coupé la connexion."));
            break;
        default:
            emit erreurReseau(trUtf8("ERREUR : ")+m_socket->errorString());
    }
}


void Reseau::donneesRecues()
{
    for(;;)
    {
        QDataStream in(m_socket);

        if (m_tailleMessage == 0)
        {
            if (m_socket->bytesAvailable() < (int)sizeof(quint16))
                 return;
            in >> m_tailleMessage;
        }

        if (m_socket->bytesAvailable() < m_tailleMessage)
            return;

        QString messageRecu;
        in >> messageRecu;
        m_tailleMessage = 0;
        QString inf = messageRecu.section('/',0,0);
        QString message = messageRecu.section('/',1);
        qDebug() << "message recu" << messageRecu;
        if(inf == "oui")
        {
            emit connexionAcceptee(messageRecu.mid(3));
        }
        else if(inf == "non")
        {
            emit connexionRefusee();
        }
        else if(inf == "otp")
        {
            emit qqdautre();
        }
        else if(inf == "cha")
        {
            emit ecritdanschat(message);
        }
        else if(inf == "con")
        {
            EntityInfo entity;
            entity.name = message.section('*', 0,0);
            entity.classe = message.section('*',1,1);
            entity.posmap = QPoint(message.section('*',2,2).toInt(), message.section('*', 3,3).toInt());
            entity.monster = (bool) message.section('*',4,4).toInt();
            emit newEntity(entity);
        }
        else if(inf == "cut")
        {
            m_gameField->recolte(message.section('*',0,0), messageRecu.section('*', 1, 1), messageRecu.section('*',2,2).toInt() , messageRecu.section('*', 3, 3).toInt());
        }
        else if(inf == "dec")
        {
            m_gameField->removeEntity(message);
        }
        else if(inf == "dep")
        {
            QPoint p(message.section('*', 1,1).toInt(), messageRecu.section('*', 2,2).toInt());
            emit deplacement(message.section('*', 0,0), p);
        }
        else if(inf == "demandeDefi")
        {
            emit onMeProposeDefi(messageRecu.section('/',1));
        }
        else if(inf == "annuleDemandeDefi")
        {
            emit ilAnnuleDemandeDefi();
        }
        else if(inf == "commenceDefi")
        {
            emit commenceDefi(message.toInt());
        }
        else if(inf == "refuseDemandeDefi")
        {
            emit ilRefuseMonDefi();
        }
        else if(inf == "cop")
        {
            m_gameField->resourceRecoltee(QPoint(message.section('*', 0, 0).toInt(), message.section('*', 1, 1).toInt()));
        }
        else if(inf == "rep")
        {
            m_gameField->resource_repousse(message.section('*', 0, 0).toInt(), message.section('*', 1, 1).toInt());
        }
        else if(inf == "ttt")
        {
            emit infoMap(message);
            //m_gameField->infos_map(message);
        }
        else if(inf == "passeTour")
        {
            m_gameField->setMonTour(false);
        }
        else if(inf == "tonTour")
        {
            emit yourTurn();
        }
        else if(inf == "gagneArme")
        {
            m_character->ajouterArme(new Weapon(message,m_data->resources));
        }
        else if(inf == "gagneEquipement")
        {
            m_character->ajouterEquipement(new Outfit(message,m_data->resources));
        }
        else if(inf == "gagneRessource")
        {
            m_character->ajouterRessource(m_data->resources->getRessource(message));
        }
        else if(inf == "commenceFight")
        {
            emit beginFight();
        }
        else if(inf == "fightVieDe")
        {
            emit changeLife(message.section('/',0,0),message.section('/',1,1).toInt());
        }
        else if(inf == "meurt")
        {
            emit meurt(message);
        }
        else if(inf == "finFight")
        {
            emit finFight(message);
        }
        else if(inf == "changePos")
        {
            m_gameField->changePos(message.section('/',0,0),message.section('/',1,1).toInt(),message.section('/',2,2).toInt());
        }
        else if(inf == "enterFight")
        {
            emit enterFight(message.section('/',0,0).toInt());
        }
        else if(inf == "newEntity")
        {
            EntityInfo entity;
            entity.name = message.section('*', 0,0);
            entity.classe = message.section('*',1,1);
            entity.posmap = QPoint(message.section('*',2,2).toInt(), message.section('*', 3,3).toInt());
            entity.monster = (bool) message.section('*',4,4).toInt();
            emit newEntity(entity);
        }
    }
}

void Reseau::envoyer(QString const& message)
{
    envoyerM(m_socket, message);
}

void envoyerM(QTcpSocket *sock, QString const& message)
{
    QByteArray paquet;
    QDataStream out(&paquet, QIODevice::WriteOnly);
    out << (quint16) 0;
    out << message;
    out.device()->seek(0);
    out << (quint16) (paquet.size() - sizeof(quint16));
    sock->write(paquet);
}
