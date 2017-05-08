#ifndef RECHERCHECHEMIN_H
#define RECHERCHECHEMIN_H

#include <QQueue>
#include <QPoint>
#include "map/path.h"
#include "map/map.h"


QQueue<Dir> faitechemFight(bool casemarchees[Map::mapWidth] [Map::mapHeight], QPoint const& arr, QVector<Path>parents, int max_dep);
QQueue<Dir> faitechemFight(bool casemarchees[Map::mapWidth] [Map::mapHeight], QVector<QPoint>const& arrivees, QVector<Path>parents, QPoint *arrivee);//on doit arriver à une des cases
QQueue<Dir> faitechem(bool casemarchees[Map::mapWidth] [Map::mapHeight], QPoint const& arr, QVector<Path>parents);
QQueue<Dir> faitechem(bool casemarchees[Map::mapWidth] [Map::mapHeight], QVector<QPoint>const& arrivees, QVector<Path>parents, QPoint *arrivee);//on doit arriver à une des cases
void case_suivante(int *x, int *y, Dir dir);
void case_suivante_simple(int *x, int *y, Dir dir);
bool caseExiste(int x, int y);

#endif // RECHERCHECHEMIN_H
