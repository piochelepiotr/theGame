#include "inventory/weapon.h"
#include "inventory/resources.h"

Weapon::Weapon(const QString &donnees, Resources *resources)
{
    m_equipement = new Outfit(donnees.section('/',0,3),resources);
    m_spell = resources->getSpell(donnees.section('/',4,4))->spellNiveau(donnees.section('/',5,5).toInt());
}

Weapon::Weapon(Outfit *equipement, Spell *spell)
{
    m_equipement = equipement;
    m_spell = spell;
}

Weapon::Weapon(Weapon const& autre)
{
    m_equipement = new Outfit(*autre.getEquipement());
    m_spell = autre.getSpell();
}

Weapon::~Weapon()
{
    delete m_equipement;
}

QString Weapon::enString(Armes const& armes)
{
    return QString::number(armes.nbr)+ '/' + enString(armes.arme);
}

QString Weapon::enString(Weapon *arme)
{
    if(arme)
        return Outfit::enString(arme->getEquipement()) + arme->getSpell()->name() + '/' + QString::number(arme->getSpell()->niveau()) + '/';
    return "-1/-1/-1/-1/-1/-1/";
}

Armes Weapon::chargeArmes(QString const& donnees,Resource *resource, Spell *spell)
{
    Armes armes;
    armes.nbr = donnees.section('/', 0,0).toInt();
    armes.arme = chargeArme(donnees.section('/', 1), resource, spell);
    return armes;
}

Weapon *Weapon::chargeArme(QString const& donnees,Resource *resource, Spell *spell)
{
    if(donnees.section('/', 0, 0).toInt() == -1)
        return 0;
    return new Weapon(Outfit::chargeEquipement(donnees.section('/', 0, 3), resource), spell);
}

QString Weapon::longue_description()
{
    QString texte = getEquipement()->longue_description();
    texte += getSpell()->longue_description();
    return texte;
}

bool operator==(Weapon const& a, Weapon const& b)
{
    if(a.getSpell() != b.getSpell())
        return false;
    return *a.getEquipement() == *b.getEquipement();
}
