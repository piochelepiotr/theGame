#ifndef MAP_H
#define MAP_H

#include "additionalActions/datamap.h"
#include "monde/combat.h"
#include "infoMonde/unmonstre.h"
#include "infoMonde/monstre.h"

class Monde;
class Ecran;

class Map : public QObject
{
    Q_OBJECT

public:
    Map(Donnees_editeur *donnees_editeur, Monde *parent, Point const& pos, Ecran *ecran);
    ~Map();
    void coupe(QPoint p);
    QString ressources_coupees() const;
    void addCombat(Personnage *leader1, Personnage *leader2);
    Combat *combat(QString nom);
    QString leaderDe(QString nom);
    void joueurChangePosDepart(QString nom, int x,int y);//pendant la phase de placement, demande une verification par le serveur
    void enEquipe(QString const& nom);
    void envoieA(QStringList noms,QString message);
    QString nomMonstre(QString const& nomClasse);
    void addMonstre();
    void connectPlayer(Joueur *joueur, bool hasJustChangedMap = false);
    void disconnectPlayer(QString const& nom);
    QList<Joueur*> joueursPasEnCombat();
    QList<Monstre*>monsterNotFighting();
    void receiveMessage(Joueur *player,QString const& begin, QString const& message);
    void analyseCombat(QString debut,QString fin,Joueur *joueur);
    void analyseReponsePnj(QString const& reponse, Joueur *player);

public slots:

    void repousse(int pos);
    void decoCombattants(QString nomCombat);
    void recoCombattants(QString nomCombat);
    void finCombat(QString nom);
    void finCombatAvantDebut(QString nom);
    void sendToPlayer(QString const& name,QString const& message);

private:
    DataMap *m_dataMap;
    QMap<QPoint, bool>m_objets_coupables;// =true si la ressource est coupé, oui c'est pas très logique je sais
    QSignalMapper *m_aide_timers;
    QMap<QPoint,QTimer*>m_timers;
    Monde *m_parent;
    Point m_pos;
    QMap<QString,Combat*>m_combats;
    QMap<QString,Monstre*>m_monstres;
    QMap<QString,Joueur*>m_joueurs;
    Ecran *m_ecran;
    Donnees_editeur *m_donnees_editeur;
};

void envoiGroupe(QList<Joueur*> const& receveurs, QString const& message, QString const& nom = "");

#endif // MAP_H
