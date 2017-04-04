#ifndef ITEM_H
#define ITEM_H

#include <QLabel>
#include "inventory/resource.h"
#include "inventory/weapon.h"
#include <QEvent>
#include "inventory/weaponModel.h"
#include <QPainter>

class ResourceItem : public QLabel
{
    Q_OBJECT
public:
    ResourceItem(Resource *resource, int quantite, int num = -1);
    ResourceItem(Outfit *equipement, int quantite, int num = -1);
    ResourceItem(Weapon *arme, int quantite, int num = -1);
    ResourceItem(OutfitModel *equipement_base, int quantite, int num = -1);
    ResourceItem(WeaponModel *arme_base, int quantite, int num = -1);
    ResourceItem(bool enable = true
            );
    void enleve(int quantite);
    void ajoute(int quantite);
    int quantite() const { return m_quantite; }
    void numMoins() { m_num--; }
signals:

    void clique(int num);
    void dbclique(int num);
    
public slots:

private:
    int m_num;
    int m_quantite;
    QPixmap m_image;
    void faitImage();
protected:

    bool eventFilter(QObject *, QEvent *);
    
};

#endif // ITEM_H
