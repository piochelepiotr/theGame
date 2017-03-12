#ifndef LESRESSOURCES_H
#define LESRESSOURCES_H

#include <QMap>
#include <QFile>
#include <QTextStream>
#include <QPainter>
#include <QImage>
#include "additionalActions/constantes.h"
#include "armebase.h"
#include "classe.h"
#include "unmonstre.h"

class Arme;


class LesRessources
{
public:
    LesRessources();
    ~LesRessources();
    Ressource *getRessource(const QString &nom) const;
    EquipementBase *getEquipement(const QString &nom) const;
    ArmeBase *getArme(const QString &nom) const;

    UnSort *getSort(QString const& nom) const;
    Classe *getClasse(QString const& nom) const;
    QMap<QString, Classe*>classes() const { return m_classes; }
    UnMonstre *getMonstre(QString const& nom) const;
    QMap<QString,UnMonstre*>monstres() const { return m_monstres; }

    void ajouteRessource(Ressource *ressource);
    void ajouteEquipement(EquipementBase *equipement);
    void ajouteArme(ArmeBase *arme);
    void ajouteSort(UnSort *sort);
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
    QMap<QString, Ressource*>m_ressources;
    QMap<QString, EquipementBase*>m_equipements;
    QMap<QString, ArmeBase*>m_armes;
    QMap<QString, UnSort*>m_sorts;
    QMap<QString, Classe*>m_classes;
    QMap<QString, UnMonstre*>m_monstres;
    QVector<QString>m_numClasses;
};

#endif // LESRESSOURCES_H
