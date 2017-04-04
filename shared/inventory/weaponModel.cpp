#include "inventory/weaponModel.h"
#include "inventory/resources.h"

WeaponModel::WeaponModel(OutfitModel *equipementBase, SpellModel *spellBase)
{
    m_equipement_base = equipementBase;
    m_spell_base = spellBase;
}

WeaponModel *WeaponModel::nouvelle(QString const& nom, const QString &chemin, Resources *resources)
{
    return new WeaponModel(OutfitModel::nouvel(nom, chemin), resources->getSpell("Coup de poing"));
}

Weapon *WeaponModel::genere()
{
    return new Weapon(getEquipement()->genere(), getSpell()->spellNiveau(0));
}

QString WeaponModel::longue_description()
{
    QString texte = getEquipement()->longue_description();
    texte += Spell::decrit(getSpell()->spellNiveau(0));
    return texte;
}
