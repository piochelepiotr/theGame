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

    Fight(Character *leader1, Character *leader2, Map *dataMap);
    ~Fight();
    void ajoutePerso(Character *perso);
    void enlevePerso(QString nom);
    void deplace(QString nom, int x, int y);
    void attaque(QString nomAttaquant,QString nomSort, int x, int y);
    void passeTour(QString nom);
    QString getNomLeader() const { return m_leader1; }
    QString getNomLeader2() const { return m_leader2; }
    bool contains(QString nom);
    bool personneSur(int x,int y);
    Character *getPersonnage(QString const& nom) const { return m_fighttants[nom]; }
    void enEquipe(int equipe1, int equipe2, QPoint const& pos1, QPoint const& pos2);
    void pret(QString nom);
    void pasPret(QString nom);
    void fightCommence();
    void toutLeMondeEstPret();
    void order();
    void nextPlayer();
    QStringList fighttants();
    Character *getCible(QPoint const& p);
    bool finFight();
    void envoieATous(QString const& message);
    void meurt(QString const& nom, bool envoyer = true);
    PhaseFight phase() const { return m_phase; }
    void setPhase(PhaseFight phase) { m_phase = phase; }
    QString gainsFin();

signals:
    void envoie(QString nom, QString message);
    void decoFighttants(QString nom);
    void s_finFight(QString const& nom);

private:

    QMap<QString,Character *>m_fighttants;
    QString m_leader1;
    QString m_leader2;
    QVector<QString> m_tours;
    QMap<QString, Character *>::iterator m_tour;
    QVector<QString>m_ordre;
    int m_nombreFighttants;
    int m_currentPlayer;
    PhaseFight m_phase;
    Map *m_dataMap;
};

#endif // COMBAT_H
