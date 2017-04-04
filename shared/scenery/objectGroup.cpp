#include "scenery/objectGroup.h"

ObjectGroup::ObjectGroup(const QString &name)
{
    m_name = name;
}

void ObjectGroup::ajouteObjet(Object *objet)
{
    m_objets[objet->numero()] = objet;
}

void ObjectGroup::supprimeObjet(Object *objet)
{
    m_objets.remove(objet->numero());
}
