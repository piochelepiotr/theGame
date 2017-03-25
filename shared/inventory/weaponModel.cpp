#include "inventory/weaponModel.h"
#include "inventory/resources.h"

WeaponModel::WeaponModel(OutfitModel *equipementBase, SpellModel *sortBase)
{
    m_equipement_base = equipementBase;
    m_sort_base = sortBase;
}

WeaponModel *WeaponModel::nouvelle(QString const& nom, const QString &chemin, Resources *ressources)
{
    return new WeaponModel(OutfitModel::nouvel(nom, chemin), ressources->getSort("Coup de poing"));
}

Weapon *WeaponModel::genere()
{
    return new Weapon(getEquipement()->genere(), getSort()->sortNiveau(0));
}

QString WeaponModel::longue_description()
{
    QString texte = getEquipement()->longue_description();
    texte += Spell::decrit(getSort()->sortNiveau(0));
    return texte;
}
