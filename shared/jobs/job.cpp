#include "jobs/jobs.h"
#include "jobs/job.h"

int xpMinlvl(int lvl)
{
    if(!lvl)
        return 0;
    return pow(lvl,PUISSANCE_METIER);
}

int lvlparxpmetier(int xp)
{
    if(!xp)
        return 1;
    return pow(xp, (double) 1/ (double) PUISSANCE_METIER);
}

int casesparlvl(int lvl)
{
    return lvl/METIER_LVLS_1CASEENPLUS + METIER_NBR_CASES_DEPART;
}

int lvlPourXCases(int nbr_cases)
{
    return qMax(1,(nbr_cases-METIER_NBR_CASES_DEPART)*METIER_LVLS_1CASEENPLUS);
}

Job::Job(JobModel *metier_base,int xp)
{
    m_metier_base = metier_base;
    m_xp = xp;
    m_lvl = lvlparxpmetier(m_xp);
    m_nbrCases = casesparlvl(m_lvl);
}

Job *Job::chargeMetier(QString const& donnees, Jobs *metiers)
{
    return new Job(metiers->metier(donnees.section('/', 0,0)),donnees.section('/', 1, 1).toInt());
}

QString Job::enString(Job *metier)
{
    return metier->getNomMetier() + '/' + QString::number(metier->m_xp) + '/';
}

void Job::gagneXp(int xpgagne)
{
    m_xp += xpgagne;
    m_lvl = lvlparxpmetier(m_xp);
    m_nbrCases = casesparlvl(m_lvl);
}

int Job::nbrCoups() const
{
    return COUPS_DEPART-(m_lvl/METIER_LVLS_1COUPSENMOINS);
}

int Job::minRessources(int lvl_resource) const
{
    int min = 1;
    if(m_lvl == METIER_NBR_LVLS && m_lvl != lvl_resource)
        min += METIER_BONUS_LVL_MAX;
    return min;
}

int Job::maxRessources(int lvl_resource) const
{
    int max = (m_lvl-lvl_resource)/METIER_LVLS_1COUPSENMOINS+2;
    if(m_lvl == METIER_NBR_LVLS && m_lvl != lvl_resource)
        max += METIER_BONUS_LVL_MAX;
    return max;
}

int Job::minRessources(qint16 objet) const
{
    return minRessources(m_metier_base->objet_coupable(objet)->lvl());
}

int Job::maxRessources(qint16 objet) const
{
    return maxRessources(m_metier_base->objet_coupable(objet)->lvl());
}

int Job::quantity_resources(qint16 objet) const
{
    int min = minRessources(objet), max = maxRessources(objet);
    return min + qrand()%(max-min+1);
}

int Job::getNbrCases()
{
    return METIER_NBR_CASES_DEPART+m_lvl/METIER_LVLS_1CASEENPLUS;
}

int xpParCase(int nbrCase)
{
    return (5+5*nbrCase)*nbrCase;//changez rien !!
}

int xpCoupeRessource(int lvlRessource)
{
    return lvlRessource*20;
}

