#include "jobs/interactiveObject.h"

Objet_coupable::Objet_coupable(Objet *objet, Objet*souche, Ressource *ressource, int lvl)
{
    m_objet = objet;
    m_souche = souche;
    m_ressource = ressource;
    m_lvl = lvl;
}
