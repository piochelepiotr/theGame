#ifndef COMBAT_H
#define COMBAT_H

#include <QString>
#include <QMap>
#include "monde/joueur.h"
#include "map/map.h"
#include <QObject>

enum PhaseFight{EnDemande,EnPlacement,EnFight,FightFini};


class Fight : public QObject
{

public:

    Q_OBJECT

public:

    Fight(Entity *leader1, Entity *leader2, Map *dataMap, int fightId);
    ~Fight();
    void addEntity(Character *perso);
    void removeEntity(QString const& name);
    void moveEntity(QString name, int x, int y);
    void attack(QString nameAttaquant,QString nameSpell, int x, int y);
    void passeTour(QString name);
    bool contains(QString name);
    bool personneSur(int x,int y);
    Entity *getEntity(QString const& name) const { return m_entities[name]; }
    void createTeams();
    void pret(QString name);
    void pasPret(QString name);
    void fightCommence();
    void toutLeMondeEstPret();
    void order();
    void nextPlayer();
    QStringList fighttants();
    QStringList characters();
    Entity *getCible(QPoint const& p);
    bool finFight();
    void envoieATous(QString const& message);
    void meurt(QString const& name, bool envoyer = true);
    PhaseFight phase() const { return m_phase; }
    void setPhase(PhaseFight phase) { m_phase = phase; }
    QString gainsFin();

signals:
    void envoie(QString const& name, QString const& message);
    void decoFighttants(int fightId);
    void s_finFight(int fightId);

private:

    void sendIfNotMonster(QString const& name,QString const& message);
    int m_fightId;
    QMap<QString,Entity *>m_entities;
    QVector<QString> m_tours;
    QMap<QString, Entity *>::iterator m_tour;
    QVector<QString>m_ordre;
    int m_quantityFighttants;
    int m_currentPlayer;
    PhaseFight m_phase;
    Map *m_dataMap;
};

#endif // COMBAT_H
