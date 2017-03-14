#ifndef EQUIPEMENTBASE_H
#define EQUIPEMENTBASE_H

#include "inventory/outfit.h"
#include "inventory/resource.h"

class EquipementBase
{
public:
    EquipementBase(Ressource *ressource, int bonus_force_min, int bonus_force_max, int bonus_vie_min, int bonus_vie_max, int bonus_points_combat_min, int bonus_points_combat_max);
    int getBonusForce(int max = 0) const { return m_bonus_force[max]; }
    int getBonusVie(int max = 0) const { return m_bonus_vie[max]; }
    int getBonusPointsCombat(int max = 0) const { return m_bonus_points_combat[max]; }
    void setBonusForce(int max, int bonus) { m_bonus_force[max] = bonus; }
    void setBonusVie(int max, int bonus) { m_bonus_vie[max] = bonus; }
    void setBonusPointCombat(int max, int bonus) { m_bonus_points_combat[max] = bonus; }
    Ressource *getRessource() const { return m_ressource; }
    static EquipementBase* nouvel(QString const& nom, QString const& chemin);
    static QString description(EquipementBase *equipement);
    QString longue_description();
    Equipement *genere();
private:
    Ressource *m_ressource;
    int m_bonus_force[2];
    int m_bonus_vie[2];
    int m_bonus_points_combat[2];
};

#endif // EQUIPEMENTBASE_H
