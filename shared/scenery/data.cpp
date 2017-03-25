#include "scenery/data.h"
#include <iostream>

Data::Data(int lcase, int hcase,int mapWidth,int mapHeight)
{
    ressources = new Resources();
    touslespnj = new NPCs();
    decor = new Scenery(lcase, hcase,mapWidth,mapHeight);
    metiers = new Jobs(ressources,decor);
}

Data::~Data()
{
    delete decor;
    delete touslespnj;
    delete ressources;
    delete metiers;
}

void Data::redidecors(int lcase, int hcase, int mapWidth, int mapHeight)
{
    decor->resize(lcase, hcase,mapWidth,mapHeight);
}
