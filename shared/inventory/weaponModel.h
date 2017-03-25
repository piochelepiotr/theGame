#ifndef ARMEBASE_H
#define ARMEBASE_H

#include "entities/spellModel.h"
#include "inventory/outfitModel.h"
#include "inventory/weapon.h"

class Resources;

class WeaponModel
{
public:
    WeaponModel(OutfitModel *equipementBase, SpellModel *sortBase);
    OutfitModel *getEquipement() const { return m_equipement_base; }
    SpellModel *getSort() const { return m_sort_base; }
    static WeaponModel *nouvelle(QString const& nom,QString const& chemin, Resources *ressources);
    void setSort(SpellModel *sort) { m_sort_base = sort; }
    Weapon *genere();
    QString longue_description();
private:
    OutfitModel *m_equipement_base;
    SpellModel *m_sort_base;
};
#endif // ARMEBASE_H
