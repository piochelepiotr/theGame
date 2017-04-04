#ifndef ServerMap_H
#define ServerMap_H

#include "map/map.h"
#include "monde/fight.h"
#include "entities/monsterModel.h"
#include "entities/monster.h"

class Monde;
class Ecran;

class ServerMap : public QObject
{
    Q_OBJECT

public:
    ServerMap(Data *donnees_editeur, Monde *parent, Point const& pos, Ecran *ecran);
    ~ServerMap();
    void coupe(QPoint p);
    QString ressources_coupees() const;
    void addFight(Character *leader1, Character *leader2);
    Fight *fight(QString nom);
    QString leaderDe(QString nom);
    void joueurChangePosDepart(QString nom, int x,int y);//pendant la phase de placement, demande une verification par le serveur
    void enEquipe(QString const& nom);
    void envoieA(QStringList noms,QString message);
    QString nomMonstre(QString const& nomClasse);
    void addMonstre();
    void connectPlayer(Joueur *joueur, bool hasJustChangedServerMap = false);
    void disconnectPlayer(QString const& nom);
    QList<Joueur*> joueursPasEnFight();
    QList<Monster*>monsterNotFighting();
    void receiveMessage(Joueur *player,QString const& begin, QString const& message);
    void analyseFight(QString debut,QString fin,Joueur *joueur);
    void analyseReponsePnj(QString const& reponse, Joueur *player);

public slots:

    void repousse(int pos);
    void decoFighttants(QString nomFight);
    void recoFighttants(QString nomFight);
    void finFight(QString nom);
    void finFightAvantDebut(QString nom);
    void sendToPlayer(QString const& name,QString const& message);

private:
    Map *m_map;
    QMap<QPoint, bool>m_objets_coupables;// =true si la ressource est coupé, oui c'est pas très logique je sais
    QSignalMapper *m_aide_timers;
    QMap<QPoint,QTimer*>m_timers;
    Monde *m_parent;
    Point m_pos;
    QMap<QString,Fight*>m_fights;
    QMap<QString,Monster*>m_monstres;
    QMap<QString,Joueur*>m_joueurs;
    Ecran *m_ecran;
    Data *m_donnees_editeur;
};

void envoiGroupe(QList<Joueur*> const& receveurs, QString const& message, QString const& nom = "");

#endif // ServerMap_H
