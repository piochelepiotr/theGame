#ifndef INVENTAIRE_H
#define INVENTAIRE_H

#include <QTabWidget>
#include "infoJoueur/personnage.h"
#include "graphicElements/items.h"
#include "additionalActions/constantes.h"

class Inventaire : public QTabWidget
{
    Q_OBJECT
public:
    Inventaire(Personnage *perso, LesRessources *ressources);
    void enleveRess(int num, int nbr);
    void enleveEquip(int num, int nbr);
    void enleveArme(int num, int nbr);
    void ajouteRess(Ressource *ress, int nbr,int same);
    void ajouteEquip(Equipement *equipement, int nbr,int same);
    void ajouteArme(Arme *arme, int nbr,int same);
    
signals:

    void s_ressclique(Ressource *ress);
    void s_equipclique(Equipement *equip);
    void s_armeclique(Arme *arme);
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

    Personnage *m_perso;
    QWidget *m_pageress;
    QWidget *m_pageequip;
    QWidget *m_pagearme;
    Items *m_items_ressources;
    Items *m_items_equipements;
    Items *m_items_armes;
    
};

class Inventaire_complet : public Inventaire
{
    Q_OBJECT
public:
    Inventaire_complet(Personnage *perso, LesRessources *ressources);
    void ajoute_ressource(Resss ressources);
    void ajoute_equipement(Eqips equipements);
    void ajoute_arme(Armes armes);
    void enlever_ressource(int num, int nbr);
    void enlever_equipement(int num, int nbr);
    void enlever_arme(int num, int nbr);
    Ressource *ressource_num(int num) const { return m_ressources[num].ress; }
    Equipement *equipement_num(int num) const { return m_equipements[num].equipement; }
    Arme *arme_num(int num) const { return m_armes[num].arme; }
    int indexRessource(Ressource *ressource);
    int indexEquipement(Equipement *equipement);
    int indexArme(Arme *arme);

private:
    QVector<Resss>m_ressources;
    QVector<Eqips>m_equipements;
    QVector<Armes>m_armes;
};

#endif // INVENTAIRE_H
