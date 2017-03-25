#include "monde/joueur.h"

Joueur::Joueur(QTcpSocket *socket) : QObject()
{
    m_socket = socket;
    m_etat = Connexion;
    m_tailleMessage = 0;
    m_compte = 0;
    m_persoactuel = -1;
}

void Joueur::envoi(QString const& message) const
{
    // Préparation du paquet
    QByteArray paquet;
    QDataStream out(&paquet, QIODevice::WriteOnly);

    out << (quint16) 0; // On écrit 0 au début du paquet pour réserver la place pour écrire la taille
    out << message; // On ajoute le message à la suite
    out.device()->seek(0); // On se replace au début du paquet
    out << (quint16) (paquet.size() - sizeof(quint16)); // On écrase le 0 qu'on avait réservé par la longueur du message

    // Envoi du paquet
    m_socket->write(paquet);
}

Joueur::~Joueur()
{
    if(m_compte)
        delete m_compte;
}

Character *Joueur::getPersoActuel() const
{
    if(m_etat == Jeu || m_etat == ChoixPersos)
    {
        return m_compte->getPerso(m_persoactuel);
    }
    else
        return 0;
}

void Joueur::connexion(Compte *compte)
{
    m_compte = compte;
    m_etat = ChoixPersos;
}

void Joueur::connexion(QString donnees,QString ndc, Data *donnees_editeur)
{
    m_compte = new Compte(donnees,ndc,donnees_editeur);
    m_etat = ChoixPersos;
}

void Joueur::deconnexion()
{
    delete m_compte;
    m_compte = 0;
    m_persoactuel = -1;
    m_etat = Connexion;
}

void Joueur::joue()
{
    m_etat = Jeu;
}

void Joueur::changePerso()
{
    m_etat = ChoixPersos;
}
