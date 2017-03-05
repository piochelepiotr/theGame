#ifndef DONNEES_EDITEUR_H
#define DONNEES_EDITEUR_H

#include "decors.h"
#include "touslesmetiers.h"
#include "touslespnj.h"
#include "infoMonde/images_classe.h"
#include "infoMonde/lesressources.h"

class Donnees_editeur
{
public:
    void redidecors(int lcase, int hcase);
    Donnees_editeur(int lcase, int hcase);
    ~Donnees_editeur();
    Decors *decor;
    TouslesPnj *touslespnj;
    Images_Classes *images_classes;
    LesRessources *ressources;
    TouslesMetiers *metiers;
};

#endif // DONNEES_EDITEUR_H
