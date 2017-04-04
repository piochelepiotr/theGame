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
#include "graphic/resourceItem.h"
#include "inventory/outfit.h"
#include "inventory/weapon.h"
#include <qmath.h>

class ResourceItems : public QHBoxLayout
{
    Q_OBJECT
public:
    ResourceItems(QVector<Resss>resources, int nbrobjh, int nbrobjv, Resources *lesresources);
    ResourceItems(QVector<Eqips>equipements, int nbrobjh, int nbrobjv, Resources *lesresources);
    ResourceItems(QVector<Armes>armes, int nbrobjh, int nbrobjv, Resources *lesresources);
    ResourceItems(int nbrPossible, int nbrMax, Resources *lesresources);
    void enlevRess(int num, int nbr);
    void ajouteRess(Resss const& a, int num);
    void ajouteEquipement(Eqips const& a, int num);
    void ajouteArme(Armes const& a, int num);
    void setItemRessource(int num, Resss const& resss);
    void setItemEquipement(int num, Eqips const& equipements);
    void setItemArme(int num, const Armes &armes);
    void setItemRessource(int num, Resource *resource, int quantity = 1);
    void setItemEquipement(int num, Outfit *equipement, int quantity = 1);
    void setItemArme(int num, Weapon *arme, int quantity = 1);
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
    QVector<ResourceItem*>m_items;
    QVector<QLabel*>m_vides;
    int m_nbrh;
    int m_nbrv;
    Resources *m_lesRessources;
};

ResourceItem *item(Resources *lesresources, Resource *resource, int quantite = 1, int num = -1);

#endif // ITEMS_H
