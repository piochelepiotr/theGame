#include "scenery/data.h"
#include <iostream>

Donnees_editeur::Donnees_editeur(int lcase, int hcase,int mapWidth,int mapHeight)
{
    ressources = new LesRessources();
    touslespnj = new TouslesPnj();
    decor = new Decors(lcase, hcase,mapWidth,mapHeight);
    metiers = new TouslesMetiers(ressources,decor);
}

Donnees_editeur::~Donnees_editeur()
{
    delete decor;
    delete touslespnj;
    delete ressources;
    delete metiers;
}

void Donnees_editeur::redidecors(int lcase, int hcase, int mapWidth, int mapHeight)
{
    decor->resize(lcase, hcase,mapWidth,mapHeight);
}
