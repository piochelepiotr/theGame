#include "inventory/inventory.h"

Inventaire_complet::Inventaire_complet(Personnage *perso, LesRessources *ressources) : Inventaire(perso, ressources)
{
    if(perso)
    {
        m_ressources = perso->getRessources();
        m_equipements = perso->getEquipements();
        m_armes = perso->getArmes();
    }
}

void Inventaire_complet::ajoute_ressource(Resss ressources)
{
    for(int i = 0; i < m_ressources.size(); i++)
    {
        if(m_ressources[i].ress == ressources.ress)
        {
            m_ressources[i].nbr += ressources.nbr;
            ajouteRess(ressources.ress, ressources.nbr, i);
            return;
        }
    }
    m_ressources.push_back(ressources);
    ajouteRess(ressources.ress,ressources.nbr, m_ressources.size()-1);
}

void Inventaire_complet::ajoute_equipement(Eqips equipements)
{
    for(int i = 0; i < m_equipements.size(); i++)
    {
        if(*(m_equipements[i].equipement) == *(equipements.equipement))
        {
            m_equipements[i].nbr += equipements.nbr;
            ajouteEquip(equipements.equipement, equipements.nbr,i);
            return;
        }
    }
    m_equipements.push_back(equipements);
    ajouteEquip(equipements.equipement,equipements.nbr, m_equipements.size()-1);
}

void Inventaire_complet::ajoute_arme(Armes armes)
{
    for(int i = 0; i < m_armes.size(); i++)
    {
        if(*(m_armes[i].arme) == *(armes.arme))
        {
            m_armes[i].nbr += armes.nbr;
            ajouteArme(armes.arme, armes.nbr, i);
            return;
        }
    }
    m_armes.push_back(armes);
    ajouteArme(armes.arme,armes.nbr, m_armes.size()-1);
}

void Inventaire_complet::enlever_ressource(int num, int nbr)
{
    m_ressources[num].nbr -= nbr;
    if(m_ressources[num].nbr < 1)
    {
        m_ressources.remove(num);
    }
    enleveRess(num, nbr);
}

void Inventaire_complet::enlever_equipement(int num, int nbr)
{
    m_equipements[num].nbr -= nbr;
    if(m_equipements[num].nbr < 1)
    {
        m_equipements.remove(num);
    }
    enleveEquip(num, nbr);
}

void Inventaire_complet::enlever_arme(int num, int nbr)
{
    m_armes[num].nbr -= nbr;
    if(m_armes[num].nbr < 1)
    {
        m_armes.remove(num);
    }
    enleveArme(num, nbr);
}

int Inventaire_complet::indexRessource(Ressource *ressource)
{
    int index = 0;
    while(index < m_ressources.size() && m_ressources[index].ress != ressource)
    {
        index++;
    }
    if(m_ressources[index].ress != ressource)
        qDebug() << "ERREUR : indexRessource demande pour ressource inexistante";
    return index;
}

int Inventaire_complet::indexEquipement(Equipement *equipement)
{
    int index = 0;
    while(index < m_equipements.size() && m_equipements[index].equipement != equipement)
    {
        index++;
    }
    if(m_equipements[index].equipement != equipement)
        qDebug() << "ERREUR : indexEquipement demande pour equipement inexistant";
    return index;
}

int Inventaire_complet::indexArme(Arme *arme)
{
    int index = 0;
    while(index < m_armes.size() && m_armes[index].arme != arme)
    {
        index++;
    }
    if(m_armes[index].arme != arme)
        qDebug() << "ERREUR : indexArme demande pour arme inexistante";
    return index;
}

Inventaire::Inventaire(Personnage *perso, LesRessources *ressources)
{
    m_perso = perso;
    m_pageress = new QWidget;
    m_pageequip = new QWidget;
    m_pagearme = new QWidget;
    m_items_ressources = new Items(perso->getRessources(), NBRRESSH, NBRRESSV, ressources);
    m_items_equipements = new Items(perso->getEquipements(), NBRRESSH, NBRRESSV, ressources);
    m_items_armes = new Items(perso->getArmes(), NBRRESSH, NBRRESSV, ressources);

    m_pageress->setLayout(m_items_ressources);
    m_pageequip->setLayout(m_items_equipements);
    m_pagearme->setLayout(m_items_armes);

    addTab(m_pageress, trUtf8("Ressources"));
    addTab(m_pageequip, trUtf8("Equipements"));
    addTab(m_pagearme, trUtf8("Armes"));

    connect(m_items_ressources, SIGNAL(ressclique(int)), this, SLOT(ressclique(int)));
    connect(m_items_equipements, SIGNAL(ressclique(int)), this, SLOT(equipclique(int)));
    connect(m_items_armes, SIGNAL(ressclique(int)), this, SLOT(armeclique(int)));
    connect(m_items_ressources, SIGNAL(ressdbclique(int)), this, SLOT(ressource_double_clique(int)));
    connect(m_items_equipements, SIGNAL(ressdbclique(int)), this, SLOT(equipdblclique(int)));
    connect(m_items_armes, SIGNAL(ressdbclique(int)), this, SLOT(armedblclique(int)));
}

void Inventaire::ressclique(int num)
{
    emit s_ressclique(m_perso->ressnum(num));
}

void Inventaire::equipclique(int num)
{
    emit s_equipclique(m_perso->equipement_num(num));
}

void Inventaire::armeclique(int num)
{
    emit s_armeclique(m_perso->armenum(num));
}

void Inventaire::ressource_double_clique(int num)
{
    emit s_ressource_double_clique(num);
}

void Inventaire::equipdblclique(int num)
{
    emit s_equipdblclique(num);
}

void Inventaire::armedblclique(int num)
{
    emit s_armedblclique(num);
}

void Inventaire::enleveRess(int num, int nbr)
{
    m_items_ressources->enlevRess(num, nbr);
}

void Inventaire::enleveEquip(int num, int nbr)
{
    m_items_equipements->enlevRess(num, nbr);
}

void Inventaire::enleveArme(int num, int nbr)
{
    m_items_armes->enlevRess(num, nbr);
}

void Inventaire::ajouteRess(Ressource *ress, int nbr,int same)
{
    Resss resss;
    resss.nbr = nbr;
    resss.ress = ress;
    m_items_ressources->ajouteRess(resss, same);
}

void Inventaire::ajouteEquip(Equipement *equipement, int nbr,int same)
{
    Eqips equipements;
    equipements.nbr = nbr;
    equipements.equipement = equipement;
    m_items_equipements->ajouteEquipement(equipements, same);
}

void Inventaire::ajouteArme(Arme *arme, int nbr,int same)
{
    Armes armes;
    armes.nbr = nbr;
    armes.arme = arme;
    m_items_armes->ajouteArme(armes, same);
}
