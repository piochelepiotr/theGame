#ifndef EQUIPEMENT_H
#define EQUIPEMENT_H

#include "infoMonde/ressource.h"
#include <QMap>
#include <QObject>
#include "additionalActions/constantes.h"
#include <QString>

class LesRessources;
class Equipement;

typedef struct Eqips Eqips;
struct Eqips
{
    int nbr;
    Equipement *equipement;
};

class Equipement
{
public:
    Equipement(QString const& donnees,LesRessources *ressources);
    Equipement(Ressource *ressource, int bonus_force, int bonus_vie, int bonus_points_combat);
    Equipement(Equipement const& autre);
    Ressource *getRessource() const { return m_ressource; }
    int getBonusForce() const { return m_bonus_force; }
    int getBonusVie() const { return m_bonus_vie; }
    int getBonusPointsCombat() const { return m_bonus_points_combat; }
    QString nom() const { return m_ressource->nom(); }

    static QString descr_effet(Equipement *equipement);
    static QString enString(Eqips const& equipements);
    static QString enString(Equipement *equipement);
    static Eqips chargeEquipements(QString const& donnees,Ressource *ressource);
    static Equipement *chargeEquipement(const QString &donnees,Ressource *ressource);
    QString longue_description();

protected:
    Ressource *m_ressource;
    int m_bonus_force;
    int m_bonus_vie;
    int m_bonus_points_combat;
};

bool operator==(Equipement const& a, Equipement const& b);

#endif // EQUIPEMENT_H
