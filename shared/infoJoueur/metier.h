#ifndef METIER_H
#define METIER_H

#include <QString>
#include "infoMonde/metier_base.h"
#include <qmath.h>

#define PUISSANCE_METIER 3

class TouslesMetiers;

class Metier
{
public:
    Metier(Metier_Base *metier_base,int xp);
    static Metier *chargeMetier(QString const& donnees, TouslesMetiers *metiers);
    static QString enString(Metier* metier);
    QString getNomMetier() const { return m_metier_base->nom(); }
    int getXp() const { return m_xp; }
    int getLvl() const { return m_lvl; }
    void gagneXp(int xpgagne);
    int getNbrCases();
    Metier_Base *getMetierBase() const { return m_metier_base; }
    int nbrCoups() const;
    int minRessources(int lvl_ressource) const;
    int maxRessources(int lvl_ressource) const;

    int minRessources(qint16 objet) const;
    int maxRessources(qint16 objet) const;
    int nombre_ressources(qint16 objet) const;
private:
    Metier_Base *m_metier_base;
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
