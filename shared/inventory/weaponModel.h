#ifndef ARMEBASE_H
#define ARMEBASE_H

#include "entities/spellModel.h"
#include "inventory/outfitModel.h"
#include "inventory/weapon.h"

class Resources;

class WeaponModel
{
public:
    WeaponModel(OutfitModel *equipementBase, SpellModel *spellBase);
    OutfitModel *getEquipement() const { return m_equipement_base; }
    SpellModel *getSpell() const { return m_spell_base; }
    static WeaponModel *nouvelle(QString const& nom,QString const& chemin, Resources *resources);
    void setSpell(SpellModel *spell) { m_spell_base = spell; }
    Weapon *genere();
    QString longue_description();
private:
    OutfitModel *m_equipement_base;
    SpellModel *m_spell_base;
};
#endif // ARMEBASE_H
