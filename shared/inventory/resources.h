#ifndef LESRESSOURCES_H
#define LESRESSOURCES_H

#include <QMap>
#include <QFile>
#include <QTextStream>
#include <QPainter>
#include <QImage>
#include "scenery/constants.h"
#include "inventory/weaponModel.h"
#include "entities/characterModel.h"
#include "entities/monsterModel.h"

class Weapon;


class Resources
{
public:
    Resources();
    ~Resources();
    Resource *getRessource(const QString &name) const;
    OutfitModel *getEquipement(const QString &name) const;
    WeaponModel *getArme(const QString &name) const;

    SpellModel *getSpell(QString const& name) const;
    CharacterModel *getClasse(QString const& name) const;
    QMap<QString, CharacterModel*>classes() const { return m_classes; }
    MonsterModel *getMonstre(QString const& name) const;
    EntityModel *getCreature(QString const& name) const;
    QMap<QString,MonsterModel*>monstres() const { return m_monstres; }

    void ajouteRessource(Resource *resource);
    void ajouteEquipement(OutfitModel *equipement);
    void ajouteArme(WeaponModel *arme);
    void ajouteSpell(SpellModel *spell);
    void enleveRessource(QString const& name);
    void enleveEquipement(QString const& name);
    void enleveArme(QString const& name);
    void enleveSpell(QString const& name);
    QStringList resources() const;
    QStringList spells() const;
    bool estUneRessource(QString const& name) const { return m_resources.contains(name); }
    bool estUnEquipement(QString const& name) const { return m_equipements.contains(name); }
    bool estUneArme(QString const& name) const { return m_armes.contains(name); }
    bool estUnSpell(QString const& name) const { return m_spells.contains(name); }

    QString classeSuivante(QString const& actuelle);
    QString classePrecedente(QString const& actuelle);


private:
    QMap<QString, Resource*>m_resources;
    QMap<QString, OutfitModel*>m_equipements;
    QMap<QString, WeaponModel*>m_armes;
    QMap<QString, SpellModel*>m_spells;
    QMap<QString, CharacterModel*>m_classes;
    QMap<QString, MonsterModel*>m_monstres;
    QVector<QString>m_numClasses;
};

#endif // LESRESSOURCES_H
