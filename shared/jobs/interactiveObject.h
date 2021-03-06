#ifndef OBJET_COUPABLE_H
#define OBJET_COUPABLE_H

#include "scenery/object.h"
#include "inventory/resource.h"

class InteractiveObject
{
public:
    InteractiveObject(Object *objet, Object*souche, Resource *resource, int lvl);
    Object *getObjet() const { return m_objet; }
    Object *getSouche() const { return m_souche; }
    Resource *getRessource() const { return m_resource; }
    int lvl() const { return m_lvl; }

private:
    Object *m_objet;
    Object *m_souche;
    Resource *m_resource;
    int m_lvl;
};

#endif // OBJET_COUPABLE_H
