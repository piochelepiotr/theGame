#include "scenery/objectGroup.h"

ObjectGroup::ObjectGroup(const QString &nom)
{
    m_nom = nom;
}

void ObjectGroup::ajouteObjet(Object *objet)
{
    m_objets[objet->numero()] = objet;
}

void ObjectGroup::supprimeObjet(Object *objet)
{
    m_objets.remove(objet->numero());
}
