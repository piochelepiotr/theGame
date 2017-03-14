#ifndef RESEAU_H
#define RESEAU_H

#include <QObject>
#include <QTcpSocket>
#include "scenery/constants.h"
#include <QPoint>
#include <QDataStream>
#include <QString>

class Reseau : public QObject
{
    Q_OBJECT
public:
    explicit Reseau(QObject *parent = 0);
    void start();
    QTcpSocket *socket() const { return m_socket; }
    ~Reseau();
    
signals:

    void erreurReseau(QString erreur);
    void connexionAcceptee(QString donnees);
    void connexionRefusee();
    void qqdautre();
    void ecritdanschat(QString message);
    void nouveauJoueur(InfoPerVis perso);
    void decJoueur(QString qui);
    void deplacement(QString qui, QPoint ou);
    void coupe(QString qui, QString verbe, int orientation, int nombre_coups);
    void ressource_coupe(QPoint pos);
    void ressource_repousse(int posx, int posy);
    void infos_map(QString infos);

    //combat
    void onMeProposeDefi(QString qui);
    void ilAnnuleDemandeDefi();
    void ilRefuseMonDefi();
    void commenceDefi(int equipe);//soit il accepte mon defi soit j'ai accepté le sien
    void passe_tour();
    void ton_tour();
    void commenceCombat();
    void changeVie(QString nom,int vie);
    void meurt(QString const& nom);
    void changePos(QString const& nom, int x,int y);
    void finCombat(QString const& texte);


    //inventaire
    void gagneArme(QString arme);
    void gagneEquipement(QString equipement);
    void gagneRessource(QString ressource);
    
public slots:

    void erreurSocket(QAbstractSocket::SocketError erreur);
    void donneesRecues();
    void envoyer(QString const& message);

private:

    QTcpSocket *m_socket;
    quint16 m_tailleMessage;
    
};

void envoyerM(QTcpSocket *sock, QString const& message);

#endif // RESEAU_H
