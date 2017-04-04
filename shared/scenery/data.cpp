#include "scenery/data.h"
#include <iostream>

Data::Data(int lcase, int hcase,int mapWidth,int mapHeight)
{
    resources = new Resources();
    touslespnj = new NPCs();
    decor = new Scenery(lcase, hcase,mapWidth,mapHeight);
    metiers = new Jobs(resources,decor);
}

Data::~Data()
{
    delete decor;
    delete touslespnj;
    delete resources;
    delete metiers;
}

void Data::redidecors(int lcase, int hcase, int mapWidth, int mapHeight)
{
    decor->resize(lcase, hcase,mapWidth,mapHeight);
}
