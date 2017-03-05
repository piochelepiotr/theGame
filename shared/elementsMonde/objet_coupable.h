#ifndef OBJET_COUPABLE_H
#define OBJET_COUPABLE_H

#include "objet.h"
#include "infoMonde/ressource.h"

class Objet_coupable
{
public:
    Objet_coupable(Objet *objet, Objet*souche, Ressource *ressource, int lvl);
    Objet *getObjet() const { return m_objet; }
    Objet *getSouche() const { return m_souche; }
    Ressource *getRessource() const { return m_ressource; }
    int lvl() const { return m_lvl; }

private:
    Objet *m_objet;
    Objet *m_souche;
    Ressource *m_ressource;
    int m_lvl;
};

#endif // OBJET_COUPABLE_H
