#ifndef INVENTAIRE_H
#define INVENTAIRE_H

#include <QTabWidget>
#include "entities/character.h"
#include "graphic/resourceItems.h"
#include "scenery/constants.h"

class Inventory : public QTabWidget
{
    Q_OBJECT
public:
    Inventory(Character *perso, Resources *ressources);
    void enleveRess(int num, int nbr);
    void enleveEquip(int num, int nbr);
    void enleveArme(int num, int nbr);
    void ajouteRess(Resource *ress, int nbr,int same);
    void ajouteEquip(Outfit *equipement, int nbr,int same);
    void ajouteArme(Weapon *arme, int nbr,int same);
    
signals:

    void s_ressclique(Resource *ress);
    void s_equipclique(Outfit *equip);
    void s_armeclique(Weapon *arme);
    void s_ressource_double_clique(int num);
    void s_equipdblclique(int num);
    void s_armedblclique(int num);
    
public slots:
    void ressclique(int num);
    void equipclique(int num);
    void armeclique(int num);
    void ressource_double_clique(int num);
    void equipdblclique(int num);
    void armedblclique(int num);

protected :

    Character *m_perso;
    QWidget *m_pageress;
    QWidget *m_pageequip;
    QWidget *m_pagearme;
    ResourceItems *m_items_ressources;
    ResourceItems *m_items_equipements;
    ResourceItems *m_items_armes;
    
};

class Inventaire_complet : public Inventory
{
    Q_OBJECT
public:
    Inventaire_complet(Character *perso, Resources *ressources);
    void ajoute_ressource(Resss ressources);
    void ajoute_equipement(Eqips equipements);
    void ajoute_arme(Armes armes);
    void enlever_ressource(int num, int nbr);
    void enlever_equipement(int num, int nbr);
    void enlever_arme(int num, int nbr);
    Resource *ressource_num(int num) const { return m_ressources[num].ress; }
    Outfit *equipement_num(int num) const { return m_equipements[num].equipement; }
    Weapon *arme_num(int num) const { return m_armes[num].arme; }
    int indexRessource(Resource *ressource);
    int indexEquipement(Outfit *equipement);
    int indexArme(Weapon *arme);

private:
    QVector<Resss>m_ressources;
    QVector<Eqips>m_equipements;
    QVector<Armes>m_armes;
};

#endif // INVENTAIRE_H
