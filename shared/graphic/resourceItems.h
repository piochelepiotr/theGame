#ifndef ITEMS_H
#define ITEMS_H

#include <QHBoxLayout>
#include <QGridLayout>
#include <QScrollBar>
#include "inventory/resource.h"
#include <QVector>
#include <QPushButton>
#include "scenery/constants.h"
#include <qmath.h>
#include "item.h"
#include "inventory/outfit.h"
#include "inventory/weapon.h"
#include <qmath.h>

class Items : public QHBoxLayout
{
    Q_OBJECT
public:
    Items(QVector<Resss>ressources, int nbrobjh, int nbrobjv, LesRessources *lesressources);
    Items(QVector<Eqips>equipements, int nbrobjh, int nbrobjv, LesRessources *lesressources);
    Items(QVector<Armes>armes, int nbrobjh, int nbrobjv, LesRessources *lesressources);
    Items(int nbrPossible, int nbrMax, LesRessources *lesressources);
    void enlevRess(int num, int nbr);
    void ajouteRess(Resss const& a, int num);
    void ajouteEquipement(Eqips const& a, int num);
    void ajouteArme(Armes const& a, int num);
    void setItemRessource(int num, Resss const& resss);
    void setItemEquipement(int num, Eqips const& equipements);
    void setItemArme(int num, const Armes &armes);
    void setItemRessource(int num, Ressource *ressource, int nombre = 1);
    void setItemEquipement(int num, Equipement *equipement, int nombre = 1);
    void setItemArme(int num, Arme *arme, int nombre = 1);
    int scrollValue() const { return m_scroll->value(); }
    
signals:

    void ressclique(int num);
    void ressdbclique(int num);
    
public slots:

    void scrool(int valeure);
    void remplire(int valeure);
    void cliqueObjet(int num);
    void dbcliqueObjet(int num);

private:

    QScrollBar *m_scroll;
    QGridLayout *m_layout;
    QVector<Item*>m_items;
    QVector<QLabel*>m_vides;
    int m_nbrh;
    int m_nbrv;
    LesRessources *m_lesRessources;
};

Item *item(LesRessources *lesressources, Ressource *ressource, int quantite = 1, int num = -1);

#endif // ITEMS_H
