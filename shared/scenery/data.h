#ifndef DONNEES_EDITEUR_H
#define DONNEES_EDITEUR_H

#include "decors.h"
#include "touslesmetiers.h"
#include "touslespnj.h"
#include "infoMonde/images_classe.h"
#include "inventory/resources.h"

class Donnees_editeur
{
public:
    void redidecors(int lcase, int hcase, int mapWidth, int mapHeight);
    Donnees_editeur(int lcase, int hcase, int mapWidth, int mapHeight);
    ~Donnees_editeur();
    Decors *decor;
    TouslesPnj *touslespnj;
    Images_Classes *images_classes;
    LesRessources *ressources;
    TouslesMetiers *metiers;
};

#endif // DONNEES_EDITEUR_H
