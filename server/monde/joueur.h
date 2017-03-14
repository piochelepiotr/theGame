#ifndef JOUEUR_H
#define JOUEUR_H

#include <QtNetwork>
#include <QString>
#include <QVector>
#include <QSettings>

#include "network/compte.h"
#include "entities/character.h"
#include "inventory/resources.h"

class Joueur : public QObject
{
public :

    Q_OBJECT

public:

    enum Etat{Connexion,ChoixPersos,CreerPerso, Jeu};

    Joueur(QTcpSocket *socket);
    ~Joueur();
    quint16 getTailleMessage() const { return m_tailleMessage; }
    QTcpSocket *getSocket() const { return m_socket; }
    QString getPseudo() const { return m_compte->getPseudo(); }
    Etat getEtat() const { return m_etat; }
    Compte *getCompte() const { return m_compte; }
    Personnage *getPersoActuel() const;

    void setPersoActuel(int num) { m_persoactuel=num; }

    void setTailleMessage(quint16 taille) { m_tailleMessage = taille; }
    void envoi(QString const& message) const;

    void connexion(Compte *compte);
    void connexion(QString donnees, QString ndc, Donnees_editeur *donnees_editeur);
    void deconnexion();
    void joue();
    void changePerso();
    QString getNdc() const { return m_compte->getNdc(); }

private:

    QTcpSocket *m_socket;
    Etat m_etat;
    quint16 m_tailleMessage;
    Compte *m_compte;
    int m_persoactuel;
};

#endif // JOUEUR_H
