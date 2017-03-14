#ifndef COMBAT_H
#define COMBAT_H

#include <QString>
#include <QMap>
#include "monde/joueur.h"
#include "map/map.h"
#include <QObject>

enum PhaseCombat{EnDemande,EnPlacement,EnCombat,CombatFini};


class Combat : public QObject
{

public:

    Q_OBJECT

public:

    Combat(Personnage *leader1, Personnage *leader2, DataMap *dataMap);
    ~Combat();
    void ajoutePerso(Personnage *perso);
    void enlevePerso(QString nom);
    void deplace(QString nom, int x, int y);
    void attaque(QString nomAttaquant,QString nomSort, int x, int y);
    void passeTour(QString nom);
    QString getNomLeader() const { return m_leader1; }
    QString getNomLeader2() const { return m_leader2; }
    bool contains(QString nom);
    bool personneSur(int x,int y);
    Personnage *getPersonnage(QString const& nom) const { return m_combattants[nom]; }
    void enEquipe(int equipe1, int equipe2, QPoint const& pos1, QPoint const& pos2);
    void pret(QString nom);
    void pasPret(QString nom);
    void combatCommence();
    void toutLeMondeEstPret();
    void order();
    void nextPlayer();
    QStringList combattants();
    Personnage *getCible(QPoint const& p);
    bool finCombat();
    void envoieATous(QString const& message);
    void meurt(QString const& nom, bool envoyer = true);
    PhaseCombat phase() const { return m_phase; }
    void setPhase(PhaseCombat phase) { m_phase = phase; }
    QString gainsFin();

signals:
    void envoie(QString nom, QString message);
    void decoCombattants(QString nom);
    void s_finCombat(QString const& nom);

private:

    QMap<QString,Personnage *>m_combattants;
    QString m_leader1;
    QString m_leader2;
    QVector<QString> m_tours;
    QMap<QString, Personnage *>::iterator m_tour;
    QVector<QString>m_ordre;
    int m_nombreCombattants;
    int m_currentPlayer;
    PhaseCombat m_phase;
    DataMap *m_dataMap;
};

#endif // COMBAT_H
