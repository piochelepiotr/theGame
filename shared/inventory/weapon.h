#ifndef ARME_H
#define ARME_H

#include "inventory/outfit.h"
#include <QString>
#include "entities/spell.h"

class Resources;

class Weapon;

typedef struct Armes Armes;
struct Armes
{
    int nbr;
    Weapon *arme;
};


class Weapon
{
public:
    Weapon(QString const& donnees, Resources *ressources);
    Weapon(Outfit *equi, Spell *sort);
    Weapon(Weapon const& autre);
    ~Weapon();
    QString nom() const { return m_equipement->nom(); }
    Outfit *getEquipement() const { return m_equipement; }
    Spell *getSort() const { return m_sort; }
    static QString enString(Armes const& armes);
    static QString enString(Weapon *arme);
    static Armes chargeArmes(QString const& donnees,Resource *ressource, Spell *sort);
    static Weapon *chargeArme(QString const& donnees,Resource *ressource, Spell *sort);
    QString longue_description();

private:
    Outfit *m_equipement;
    Spell *m_sort;
};

bool operator==(Weapon const& a, Weapon const& b);

#endif // ARME_H
