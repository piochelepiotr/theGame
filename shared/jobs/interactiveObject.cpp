#include "jobs/interactiveObject.h"

InteractiveObject::InteractiveObject(Object *objet, Object*souche, Resource *ressource, int lvl)
{
    m_objet = objet;
    m_souche = souche;
    m_ressource = ressource;
    m_lvl = lvl;
}
