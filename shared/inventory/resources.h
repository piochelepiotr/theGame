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
    Resource *getRessource(const QString &nom) const;
    OutfitModel *getEquipement(const QString &nom) const;
    WeaponModel *getArme(const QString &nom) const;

    SpellModel *getSort(QString const& nom) const;
    CharacterModel *getClasse(QString const& nom) const;
    QMap<QString, CharacterModel*>classes() const { return m_classes; }
    MonsterModel *getMonstre(QString const& nom) const;
    EntityModel *getCreature(QString const& name) const;
    QMap<QString,MonsterModel*>monstres() const { return m_monstres; }

    void ajouteRessource(Resource *ressource);
    void ajouteEquipement(OutfitModel *equipement);
    void ajouteArme(WeaponModel *arme);
    void ajouteSort(SpellModel *sort);
    void enleveRessource(QString const& nom);
    void enleveEquipement(QString const& nom);
    void enleveArme(QString const& nom);
    void enleveSort(QString const& nom);
    QStringList ressources() const;
    QStringList sorts() const;
    bool estUneRessource(QString const& nom) const { return m_ressources.contains(nom); }
    bool estUnEquipement(QString const& nom) const { return m_equipements.contains(nom); }
    bool estUneArme(QString const& nom) const { return m_armes.contains(nom); }
    bool estUnSort(QString const& nom) const { return m_sorts.contains(nom); }

    QString classeSuivante(QString const& actuelle);
    QString classePrecedente(QString const& actuelle);


private:
    QMap<QString, Resource*>m_ressources;
    QMap<QString, OutfitModel*>m_equipements;
    QMap<QString, WeaponModel*>m_armes;
    QMap<QString, SpellModel*>m_sorts;
    QMap<QString, CharacterModel*>m_classes;
    QMap<QString, MonsterModel*>m_monstres;
    QVector<QString>m_numClasses;
};

#endif // LESRESSOURCES_H
