#ifndef DONNEES_EDITEUR_H
#define DONNEES_EDITEUR_H

#include "scenery/scenery.h"
#include "jobs/jobs.h"
#include "entities/npcs.h"
#include "entities/entityImage.h"
#include "inventory/resources.h"

class Data
{
public:
    void redidecors(int lcase, int hcase, int mapWidth, int mapHeight);
    Data(int lcase, int hcase, int mapWidth, int mapHeight);
    ~Data();
    Scenery *decor;
    NPCs *touslespnj;
    ImagesEntities *images_classes;
    Resources *resources;
    Jobs *metiers;
};

#endif // DONNEES_EDITEUR_H
