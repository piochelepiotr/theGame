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
    QString resources_coupees() const;
    void addFight(Character *leader1, Character *leader2);
    Fight *fight(QString name);
    QString leaderDe(QString name);
    void joueurChangePosDepart(QString name, int x,int y);//pendant la phase de placement, demande une verification par le serveur
    void enEquipe(QString const& name);
    void envoieA(QStringList names,QString message);
    QString nameMonstre(QString const& nameClasse);
    void addMonstre();
    void connectPlayer(Joueur *joueur, bool hasJustChangedServerMap = false);
    void disconnectPlayer(QString const& name);
    QList<Joueur*> joueursPasEnFight();
    QList<Monster*>monsterNotFighting();
    void receiveMessage(Joueur *player,QString const& begin, QString const& message);
    void analyseFight(QString debut,QString fin,Joueur *joueur);
    void analyseReponsePnj(QString const& reponse, Joueur *player);

public slots:

    void repousse(int pos);
    void decoFighttants(QString nameFight);
    void recoFighttants(QString nameFight);
    void finFight(QString name);
    void finFightAvantDebut(QString name);
    void sendToPlayer(QString const& name,QString const& message);

private:
    Map *m_map;
    QMap<QPoint, bool>m_objets_coupables;// =true si la resource est coupé, oui c'est pas très logique je sais
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

void envoiGroupe(QList<Joueur*> const& receveurs, QString const& message, QString const& name = "");

#endif // ServerMap_H
