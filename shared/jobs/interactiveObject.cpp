#include "jobs/interactiveObject.h"

InteractiveObject::InteractiveObject(Object *objet, Object*souche, Resource *resource, int lvl)
{
    m_objet = objet;
    m_souche = souche;
    m_resource = resource;
    m_lvl = lvl;
}
