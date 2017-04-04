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
    Weapon(QString const& donnees, Resources *resources);
    Weapon(Outfit *equi, Spell *spell);
    Weapon(Weapon const& autre);
    ~Weapon();
    QString name() const { return m_equipement->name(); }
    Outfit *getEquipement() const { return m_equipement; }
    Spell *getSpell() const { return m_spell; }
    static QString enString(Armes const& armes);
    static QString enString(Weapon *arme);
    static Armes chargeArmes(QString const& donnees,Resource *resource, Spell *spell);
    static Weapon *chargeArme(QString const& donnees,Resource *resource, Spell *spell);
    QString longue_description();

private:
    Outfit *m_equipement;
    Spell *m_spell;
};

bool operator==(Weapon const& a, Weapon const& b);

#endif // ARME_H
