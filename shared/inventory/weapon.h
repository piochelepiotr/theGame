#ifndef ARME_H
#define ARME_H

#include "inventory/outfit.h"
#include <QString>
#include "entities/spell.h"

class LesRessources;

class Arme;

typedef struct Armes Armes;
struct Armes
{
    int nbr;
    Arme *arme;
};


class Arme
{
public:
    Arme(QString const& donnees, LesRessources *ressources);
    Arme(Equipement *equi, Sort *sort);
    Arme(Arme const& autre);
    ~Arme();
    QString nom() const { return m_equipement->nom(); }
    Equipement *getEquipement() const { return m_equipement; }
    Sort *getSort() const { return m_sort; }
    static QString enString(Armes const& armes);
    static QString enString(Arme *arme);
    static Armes chargeArmes(QString const& donnees,Ressource *ressource, Sort *sort);
    static Arme *chargeArme(QString const& donnees,Ressource *ressource, Sort *sort);
    QString longue_description();

private:
    Equipement *m_equipement;
    Sort *m_sort;
};

bool operator==(Arme const& a, Arme const& b);

#endif // ARME_H
