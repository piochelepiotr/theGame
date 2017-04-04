#ifndef EQUIPEMENTBASE_H
#define EQUIPEMENTBASE_H

#include "inventory/outfit.h"
#include "inventory/resource.h"

class OutfitModel
{
public:
    OutfitModel(Resource *ressource, int bonus_force_min, int bonus_force_max, int bonus_vie_min, int bonus_vie_max, int bonus_points_fight_min, int bonus_points_fight_max);
    int getBonusForce(int max = 0) const { return m_bonus_force[max]; }
    int getBonusVie(int max = 0) const { return m_bonus_vie[max]; }
    int getBonusPointsFight(int max = 0) const { return m_bonus_points_fight[max]; }
    void setBonusForce(int max, int bonus) { m_bonus_force[max] = bonus; }
    void setBonusVie(int max, int bonus) { m_bonus_vie[max] = bonus; }
    void setBonusPointFight(int max, int bonus) { m_bonus_points_fight[max] = bonus; }
    Resource *getRessource() const { return m_ressource; }
    static OutfitModel* nouvel(QString const& nom, QString const& chemin);
    static QString description(OutfitModel *equipement);
    QString longue_description();
    Outfit *genere();
private:
    Resource *m_ressource;
    int m_bonus_force[2];
    int m_bonus_vie[2];
    int m_bonus_points_fight[2];
};

#endif // EQUIPEMENTBASE_H
