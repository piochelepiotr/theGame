#include "inventory/weapon.h"
#include "inventory/resources.h"

Weapon::Weapon(const QString &donnees, Resources *ressources)
{
    m_equipement = new Outfit(donnees.section('/',0,3),ressources);
    m_sort = ressources->getSort(donnees.section('/',4,4))->sortNiveau(donnees.section('/',5,5).toInt());
}

Weapon::Weapon(Outfit *equipement, Spell *sort)
{
    m_equipement = equipement;
    m_sort = sort;
}

Weapon::Weapon(Weapon const& autre)
{
    m_equipement = new Outfit(*autre.getEquipement());
    m_sort = autre.getSort();
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
        return Outfit::enString(arme->getEquipement()) + arme->getSort()->nom() + '/' + QString::number(arme->getSort()->niveau()) + '/';
    return "-1/-1/-1/-1/-1/-1/";
}

Armes Weapon::chargeArmes(QString const& donnees,Resource *ressource, Spell *sort)
{
    Armes armes;
    armes.nbr = donnees.section('/', 0,0).toInt();
    armes.arme = chargeArme(donnees.section('/', 1), ressource, sort);
    return armes;
}

Weapon *Weapon::chargeArme(QString const& donnees,Resource *ressource, Spell *sort)
{
    if(donnees.section('/', 0, 0).toInt() == -1)
        return 0;
    return new Weapon(Outfit::chargeEquipement(donnees.section('/', 0, 3), ressource), sort);
}

QString Weapon::longue_description()
{
    QString texte = getEquipement()->longue_description();
    texte += getSort()->longue_description();
    return texte;
}

bool operator==(Weapon const& a, Weapon const& b)
{
    if(a.getSort() != b.getSort())
        return false;
    return *a.getEquipement() == *b.getEquipement();
}
