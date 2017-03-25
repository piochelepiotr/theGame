#ifndef METIER_H
#define METIER_H

#include <QString>
#include "jobs/jobModel.h"
#include <qmath.h>

#define PUISSANCE_METIER 3

class Jobs;

class Job
{
public:
    Job(JobModel *metier_base,int xp);
    static Job *chargeMetier(QString const& donnees, Jobs *metiers);
    static QString enString(Job* metier);
    QString getNomMetier() const { return m_metier_base->nom(); }
    int getXp() const { return m_xp; }
    int getLvl() const { return m_lvl; }
    void gagneXp(int xpgagne);
    int getNbrCases();
    JobModel *getMetierBase() const { return m_metier_base; }
    int nbrCoups() const;
    int minRessources(int lvl_ressource) const;
    int maxRessources(int lvl_ressource) const;

    int minRessources(qint16 objet) const;
    int maxRessources(qint16 objet) const;
    int nombre_ressources(qint16 objet) const;
private:
    JobModel *m_metier_base;
    int m_xp;
    int m_lvl;
    int m_nbrCases;
};

int xpMinlvl(int lvl);
int lvlparxp(int xp);
int casesparlvl(int lvl);
int lvlPourXCases(int nbr_cases);
int xpParCase(int nbrCase);
int xpCoupeRessource(int lvlRessource);

#endif // METIER_H
