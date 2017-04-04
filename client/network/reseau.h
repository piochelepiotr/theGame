#ifndef RESEAU_H
#define RESEAU_H

#include <QObject>
#include <QTcpSocket>
#include "scenery/constants.h"
#include <QPoint>
#include <QDataStream>
#include <QString>

class Character;
class GameField;
class Data;

class Reseau : public QObject
{
    Q_OBJECT
public:
    explicit Reseau(Data *data,QObject *parent = 0);
    void start();
    QTcpSocket *socket() const { return m_socket; }
    ~Reseau();

    void setCharacter(Character *character) { m_character = character; }
    void setGameField(GameField *gameField) { m_gameField = gameField; }
    
signals:

    void erreurReseau(QString erreur);
    void connexionAcceptee(QString donnees);
    void connexionRefusee();
    void qqdautre();
    void ecritdanschat(QString message);
    void deplacement(QString qui, QPoint ou);

    //fight
    void onMeProposeDefi(QString qui);
    void ilAnnuleDemandeDefi();
    void ilRefuseMonDefi();
    void commenceDefi(int equipe);//soit il accepte mon defi soit j'ai accepté le sien
    void meurt(QString const& name);
    void finFight(QString const& texte);
    
public slots:

    void erreurSocket(QAbstractSocket::SocketError erreur);
    void donneesRecues();
    void envoyer(QString const& message);

private:

    QTcpSocket *m_socket;
    quint16 m_tailleMessage;

    GameField *m_gameField;
    Character *m_character;
    Data *m_data;
};

void envoyerM(QTcpSocket *sock, QString const& message);

#endif // RESEAU_H
