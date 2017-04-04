#include "graphic/ecran.h"

Ecran::Ecran() : QWidget()
{
    m_donnees_editeur = new Data(0,0,0,0);
    setWindowTitle(trUtf8("serveur DU jeu"));
    m_infoServeur = new QLabel;
    m_infojoueurs = new QListWidget;
    m_layout = new QVBoxLayout;
    m_boutonQuitter = new QPushButton(trUtf8("Quitter"), this);
    QObject::connect(m_boutonQuitter, SIGNAL(clicked()), qApp, SLOT(quit()));
    m_layout->addWidget(m_infojoueurs);
    m_layout->addWidget(m_boutonQuitter);
    m_layout->addWidget(m_infoServeur);
    setLayout(m_layout);
    m_db = new DataBase(m_donnees_editeur);
    m_socketserveur = new QTcpServer(this);
    if (!m_socketserveur->listen(QHostAddress::Any, PORT))// Démarrage du serveur sur toutes les IP disponibles et sur le port x
    {
        // Si le serveur n'a pas été démarré correctement
        m_infoServeur->setText(trUtf8("Le serveur n'a pas pu etre démarré. Raison :<br />") + m_socketserveur->errorString());
    }
    else
    {
        // Si le serveur a été démarré correctement
        m_infoServeur->setText(trUtf8("Le serveur a été démarré sur le port <strong>") + QString::number(m_socketserveur->serverPort()) + tr("</strong>.<br />Des joueurs peuvent maintenant se connecter."));
        connect(m_socketserveur, SIGNAL(newConnection()), this, SLOT(nouvelleConnexion()));
    }
    m_monde = new Monde(m_donnees_editeur,this);
    //connect(m_monde, SIGNAL(repousse(Point,int,int)), this, SLOT(ressource_repousse(Point,int,int)));
    //connect(m_monde,SIGNAL(s_envoie(QString,QString)),this,SLOT(envoie(QString,QString)));
}

Ecran::~Ecran()
{
    delete m_monde;
    delete m_donnees_editeur;
    delete m_db;
}

void Ecran::nouvelleConnexion()
{
    Joueur *nouveauJoueur = new Joueur(m_socketserveur->nextPendingConnection());
    m_joueurs[nouveauJoueur->getSocket()] = nouveauJoueur;

    connect(nouveauJoueur->getSocket(), SIGNAL(readyRead()), this, SLOT(donneesRecues()));
    connect(nouveauJoueur->getSocket(), SIGNAL(disconnected()), this, SLOT(deconnexionClient()));
}

void Ecran::donneesRecues()
{
    for(;;)
    {
        quint16 n;
        QString message, p, mdp;
        Joueur *joueur = NULL;
        joueur = m_joueurs[qobject_cast<QTcpSocket *>(sender())];
        if(joueur==0)
            return;
        QDataStream in(joueur->getSocket());
        if (joueur->getTailleMessage() == 0) // Si on ne connaît pas encore la taille du message, on essaie de la récupérer
        {
            if (joueur->getSocket()->bytesAvailable() < (int)sizeof(quint16)) // On n'a pas reçu la taille du message en entier
                 return;

            in >> n; // Si on a reçu la taille du message en entier, on la récupère
            joueur->setTailleMessage(n);
        }
        if (joueur->getSocket()->bytesAvailable() < joueur->getTailleMessage()) // Si on n'a pas encore tout reçu, on arrête la méthode
            return;
        in >> message;


        //m_infojoueurs->addItem(new QListWidgetItem(trUtf8("données recues : ")+message));
        qDebug() << "donnees recues : " << message;

        QString debut = message.section('/',0,0);
        QString fin = message.section('/',1);

        if(joueur->getEtat() == Joueur::Connexion)
        {
            if(debut == "ess")
            {
                message = fin;
                p = message.section('*', 0,0);//pseudo
                mdp = message.section('*', 1,1);//mot de passe
                Compte *compte = m_db->tryConnection(p,mdp,message);
                if(compte)//si le compte existe
                {
                    qDebug() << "il a donne les bons identifiants !!";
                    //message = chargePerso(p);
                    //m_infojoueurs->addItem(new QListWidgetItem(message));
                    //joueur->connexion(message, p, m_donnees_editeur);
                    joueur->connexion(compte);

                    if(m_joueursCo.contains(joueur->getPseudo()))
                    {
                        m_joueursCo[joueur->getPseudo()]->envoi("otp");


                        enleveJeu(m_joueursCo[joueur->getPseudo()]);
                        enleveChoixPerso(m_joueursCo[joueur->getPseudo()]);
                        //des problème ici
                        //message = chargePerso(p);
                        joueur->deconnexion();
                        joueur->connexion(message, p, m_donnees_editeur);
                    }
                    m_infojoueurs->addItem(new QListWidgetItem(trUtf8("message envoyé : oui")+message));
                    joueur->envoi("oui/"+message);
                    m_joueursCo[joueur->getPseudo()] = joueur;
                }
                else
                {
                    m_infojoueurs->addItem(new QListWidgetItem(trUtf8("message envoyé : non")));
                    joueur->envoi("non");
                }
            }
        }
        else if(joueur->getEtat() == Joueur::ChoixPersos)
        {
            if(message == "dec")
            {
                enleveChoixPerso(joueur);
            }
            else if(debut == "jeu")
            {

                joueur->setPersoActuel(fin.toInt());
                m_monde->connectPlayer(joueur);
                m_infojoueurs->addItem(new QListWidgetItem(trUtf8("Connexion de ")+joueur->getPersoActuel()->getNom()));
                /*joueur->joue();
                QList<Joueur*>lesautres = joueursPasEnFight(joueur->getPersoActuel()->getPos());
                message = "ttt/"+m_monde->map(joueur->getPersoActuel()->getPos())->ressources_coupees()+'/';
                for(int i = 0; i < lesautres.size(); i++)
                {
                    message += lesautres[i]->getPersoActuel()->important()+'/';
                }
                joueur->envoi(message);
                envoiGroupe(joueursPasEnFight(joueur->getPersoActuel()->getPos()), "con/"+joueur->getPersoActuel()->important());*/
                //m_joueurenJeu.insert(joueur->getPersoActuel()->getPos(), joueur);
                //m_nomJoueursEnJeu[joueur->getPersoActuel()->getNom()] = joueur;
            }
            else if(debut == "new")
            {
                //QMessageBox::critical(this, "titre", "message= "+fin);
                joueur->getCompte()->ajouteUnPerso(new Character(fin, m_donnees_editeur));
            }
            else if(debut == "spr")
            {
                joueur->getCompte()->supprimme(fin.toInt());
            }
        }
        else if(joueur->getEtat() == Joueur::Jeu)
        {
            m_monde->map(joueur->getPersoActuel()->getPos())->receiveMessage(joueur,debut,fin);
        }

        joueur->setTailleMessage(0);
    }
}

/*QList<Joueur*>Ecran::joueursPasEnFight(Point const& p)
{
    QList<Joueur*> tous = m_joueurenJeu.values(p);
    QList<Joueur*>pasEnFight;
    for(int j = 0; j < tous.size(); j++)
    {
        if(!tous.at(j)->getPersoActuel()->enFight())
        {
            pasEnFight.append(tous.at(j));
        }
    }
    return pasEnFight;
}*/

void Ecran::deconnexionClient()
{
    QTcpSocket *sock=qobject_cast<QTcpSocket *>(sender());
    Joueur *joueur = m_joueurs[sock];
    if(joueur==0)
        return;

    m_joueurs.remove(sock);
    if(joueur->getEtat() == Joueur::ChoixPersos)
    {
        enleveChoixPerso(joueur);
    }
    else if(joueur->getEtat() == Joueur::Jeu)
    {
        enleveJeu(joueur);
        enleveChoixPerso(joueur);
    }
    delete joueur;
    sock->deleteLater();
}

void Ecran::enleveJeu(Joueur *joueur)
{
    //m_infojoueurs->addItem(new QListWidgetItem(joueur->getPersoActuel()->getNom()+" sort du jeu."));
    /*Personnage *pers = joueur->getPersoActuel();
    if(pers->enFight())
    {
        Fight *fight = m_monde->map(pers->getPos())->fight(m_monde->map(pers->getPos())->leaderDe(pers->getNom()));
        fight->enlevePerso(pers->getNom());
    }
    else
    {
        envoiGroupe(joueursPasEnFight(joueur->getPersoActuel()->getPos()), "dec/"+joueur->getPersoActuel()->getNom());
    }*/
    //m_joueurenJeu.remove(joueur->getPersoActuel()->getPos(), joueur);
    //m_nomJoueursEnJeu.remove(joueur->getPersoActuel()->getNom());
    //joueur->changePerso();
    m_monde->disconnectPlayer(joueur->getPersoActuel()->getNom());
}

void Ecran::enleveChoixPerso(Joueur *joueur)
{
    joueur->getCompte()->save(m_db);
    m_joueursCo.remove(joueur->getPseudo());
    joueur->deconnexion();
}









