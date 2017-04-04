#ifndef EQUIPEMENT_H
#define EQUIPEMENT_H

#include "inventory/resource.h"
#include <QMap>
#include <QObject>
#include "scenery/constants.h"
#include <QString>

class Resources;
class Outfit;

typedef struct Eqips Eqips;
struct Eqips
{
    int nbr;
    Outfit *equipement;
};

class Outfit
{
public:
    Outfit(QString const& donnees,Resources *resources);
    Outfit(Resource *resource, int bonus_force, int bonus_vie, int bonus_points_fight);
    Outfit(Outfit const& autre);
    Resource *getRessource() const { return m_resource; }
    int getBonusForce() const { return m_bonus_force; }
    int getBonusVie() const { return m_bonus_vie; }
    int getBonusPointsFight() const { return m_bonus_points_fight; }
    QString name() const { return m_resource->name(); }

    static QString descr_effet(Outfit *equipement);
    static QString enString(Eqips const& equipements);
    static QString enString(Outfit *equipement);
    static Eqips chargeEquipements(QString const& donnees,Resource *resource);
    static Outfit *chargeEquipement(const QString &donnees,Resource *resource);
    QString longue_description();

protected:
    Resource *m_resource;
    int m_bonus_force;
    int m_bonus_vie;
    int m_bonus_points_fight;
};

bool operator==(Outfit const& a, Outfit const& b);

#endif // EQUIPEMENT_H
