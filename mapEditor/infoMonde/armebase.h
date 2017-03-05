#ifndef ARMEBASE_H
#define ARMEBASE_H

#include "unsort.h"
#include "equipementbase.h"
#include "infoJoueur/arme.h"

class LesRessources;

class ArmeBase
{
public:
    ArmeBase(EquipementBase *equipementBase, UnSort *sortBase);
    EquipementBase *getEquipement() const { return m_equipement_base; }
    UnSort *getSort() const { return m_sort_base; }
    static ArmeBase *nouvelle(QString const& nom,QString const& chemin, LesRessources *ressources);
    void setSort(UnSort *sort) { m_sort_base = sort; }
    Arme *genere();
    QString longue_description();
private:
    EquipementBase *m_equipement_base;
    UnSort *m_sort_base;
};
#endif // ARMEBASE_H
