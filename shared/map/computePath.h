#ifndef RECHERCHECHEMIN_H
#define RECHERCHECHEMIN_H

#include <QQueue>
#include <QPoint>
#include "scenery/constants.h"
#include "map/path.h"



QQueue<Dir> faitechemFight(bool casemarchees[NBR_CASES_L] [NBR_CASES_H], QPoint const& arr, QVector<Path>parents, int max_dep);
QQueue<Dir> faitechemFight(bool casemarchees[NBR_CASES_L] [NBR_CASES_H], QVector<QPoint>const& arrivees, QVector<Path>parents, QPoint *arrivee);//on doit arriver à une des cases
QQueue<Dir> faitechem(bool casemarchees[NBR_CASES_L] [NBR_CASES_H], QPoint const& arr, QVector<Path>parents);
QQueue<Dir> faitechem(bool casemarchees[NBR_CASES_L] [NBR_CASES_H], QVector<QPoint>const& arrivees, QVector<Path>parents, QPoint *arrivee);//on doit arriver à une des cases
void case_suivante(int *x, int *y, Dir dir);
void case_suivante_simple(int *x, int *y, Dir dir);
bool caseExiste(int x, int y);

#endif // RECHERCHECHEMIN_H
