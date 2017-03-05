#include "donnees_editeur.h"
#include <iostream>

Donnees_editeur::Donnees_editeur(int lcase, int hcase)
{
    ressources = new LesRessources();
    touslespnj = new TouslesPnj();
    decor = new Decors(lcase, hcase);
    metiers = new TouslesMetiers(ressources,decor);
}

Donnees_editeur::~Donnees_editeur()
{
    delete decor;
    delete touslespnj;
    delete ressources;
    delete metiers;
}

void Donnees_editeur::redidecors(int lcase, int hcase)
{
    decor->resize(lcase, hcase);
}
