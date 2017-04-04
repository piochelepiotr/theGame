#include "inventory/inventory.h"

Inventaire_complet::Inventaire_complet(Character *perso, Resources *resources) : Inventory(perso, resources)
{
    if(perso)
    {
        m_resources = perso->getRessources();
        m_equipements = perso->getEquipements();
        m_armes = perso->getArmes();
    }
}

void Inventaire_complet::ajoute_resource(Resss resources)
{
    for(int i = 0; i < m_resources.size(); i++)
    {
        if(m_resources[i].ress == resources.ress)
        {
            m_resources[i].nbr += resources.nbr;
            ajouteRess(resources.ress, resources.nbr, i);
            return;
        }
    }
    m_resources.push_back(resources);
    ajouteRess(resources.ress,resources.nbr, m_resources.size()-1);
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

void Inventaire_complet::enlever_resource(int num, int nbr)
{
    m_resources[num].nbr -= nbr;
    if(m_resources[num].nbr < 1)
    {
        m_resources.remove(num);
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

int Inventaire_complet::indexRessource(Resource *resource)
{
    int index = 0;
    while(index < m_resources.size() && m_resources[index].ress != resource)
    {
        index++;
    }
    if(m_resources[index].ress != resource)
        qDebug() << "ERREUR : indexRessource demande pour resource inexistante";
    return index;
}

int Inventaire_complet::indexEquipement(Outfit *equipement)
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

int Inventaire_complet::indexArme(Weapon *arme)
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

Inventory::Inventory(Character *perso, Resources *resources)
{
    m_perso = perso;
    m_pageress = new QWidget;
    m_pageequip = new QWidget;
    m_pagearme = new QWidget;
    m_items_resources = new ResourceItems(perso->getRessources(), NBRRESSH, NBRRESSV, resources);
    m_items_equipements = new ResourceItems(perso->getEquipements(), NBRRESSH, NBRRESSV, resources);
    m_items_armes = new ResourceItems(perso->getArmes(), NBRRESSH, NBRRESSV, resources);

    m_pageress->setLayout(m_items_resources);
    m_pageequip->setLayout(m_items_equipements);
    m_pagearme->setLayout(m_items_armes);

    addTab(m_pageress, trUtf8("Ressources"));
    addTab(m_pageequip, trUtf8("Equipements"));
    addTab(m_pagearme, trUtf8("Armes"));

    connect(m_items_resources, SIGNAL(ressclique(int)), this, SLOT(ressclique(int)));
    connect(m_items_equipements, SIGNAL(ressclique(int)), this, SLOT(equipclique(int)));
    connect(m_items_armes, SIGNAL(ressclique(int)), this, SLOT(armeclique(int)));
    connect(m_items_resources, SIGNAL(ressdbclique(int)), this, SLOT(resource_double_clique(int)));
    connect(m_items_equipements, SIGNAL(ressdbclique(int)), this, SLOT(equipdblclique(int)));
    connect(m_items_armes, SIGNAL(ressdbclique(int)), this, SLOT(armedblclique(int)));
}

void Inventory::ressclique(int num)
{
    emit s_ressclique(m_perso->ressnum(num));
}

void Inventory::equipclique(int num)
{
    emit s_equipclique(m_perso->equipement_num(num));
}

void Inventory::armeclique(int num)
{
    emit s_armeclique(m_perso->armenum(num));
}

void Inventory::resource_double_clique(int num)
{
    emit s_resource_double_clique(num);
}

void Inventory::equipdblclique(int num)
{
    emit s_equipdblclique(num);
}

void Inventory::armedblclique(int num)
{
    emit s_armedblclique(num);
}

void Inventory::enleveRess(int num, int nbr)
{
    m_items_resources->enlevRess(num, nbr);
}

void Inventory::enleveEquip(int num, int nbr)
{
    m_items_equipements->enlevRess(num, nbr);
}

void Inventory::enleveArme(int num, int nbr)
{
    m_items_armes->enlevRess(num, nbr);
}

void Inventory::ajouteRess(Resource *ress, int nbr,int same)
{
    Resss resss;
    resss.nbr = nbr;
    resss.ress = ress;
    m_items_resources->ajouteRess(resss, same);
}

void Inventory::ajouteEquip(Outfit *equipement, int nbr,int same)
{
    Eqips equipements;
    equipements.nbr = nbr;
    equipements.equipement = equipement;
    m_items_equipements->ajouteEquipement(equipements, same);
}

void Inventory::ajouteArme(Weapon *arme, int nbr,int same)
{
    Armes armes;
    armes.nbr = nbr;
    armes.arme = arme;
    m_items_armes->ajouteArme(armes, same);
}
