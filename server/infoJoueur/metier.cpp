#include "infoMonde/metier.h"
#include <qmath.h>

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

Metier::Metier(Metier_Base *metier_base,int xp)
{
    m_metier_base = metier_base;
    m_xp = xp;
    m_lvl = lvlparxpmetier(m_xp);
    m_nbrCases = casesparlvl(m_lvl);
}

Metier *Metier::chargeMetier(QString const& donnees, TouslesMetiers *metiers)
{
    return new Metier(metiers->metier(donnees.section('/', 0,0)),donnees.section('/', 1, 1).toInt());
}

QString Metier::enString(Metier *metier)
{
    return metier->getNomMetier() + '/' + QString::number(metier->m_xp) + '/';
}

void Metier::gagneXp(int xpgagne)
{
    m_xp += xpgagne;
    m_lvl = lvlparxpmetier(m_xp);
    m_nbrCases = casesparlvl(m_lvl);
}

int Metier::nbrCoups() const
{
    return COUPS_DEPART-(m_lvl/METIER_LVLS_1COUPSENMOINS);
}

int Metier::minRessources(int lvl_ressource) const
{
    int min = 1;
    if(m_lvl == METIER_NBR_LVLS && m_lvl != lvl_ressource)
        min += METIER_BONUS_LVL_MAX;
    return min;
}

int Metier::maxRessources(int lvl_ressource) const
{
    int max = (m_lvl-lvl_ressource)/METIER_LVLS_1COUPSENMOINS+2;
    if(m_lvl == METIER_NBR_LVLS && m_lvl != lvl_ressource)
        max += METIER_BONUS_LVL_MAX;
    return max;
}

int Metier::minRessources(qint16 objet) const
{
    return minRessources(m_metier_base->objet_coupable(objet)->lvl());
}

int Metier::maxRessources(qint16 objet) const
{
    return maxRessources(m_metier_base->objet_coupable(objet)->lvl());
}

int Metier::nombre_ressources(qint16 objet) const
{
    int min = minRessources(objet), max = maxRessources(objet);
    return min + qrand()%(max-min+1);
}

int Metier::getNbrCases()
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

