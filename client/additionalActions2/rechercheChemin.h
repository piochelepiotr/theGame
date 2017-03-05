#ifndef RECHERCHECHEMIN_H
#define RECHERCHECHEMIN_H

#include <QQueue>
#include <QPoint>
#include "additionalActions/constantes.h"
#include "unchemin.h"



QQueue<Dir> faitechemCombat(bool casemarchees[NBR_CASES_L] [NBR_CASES_H], QPoint const& arr, QVector<UnChemin>parents, int max_dep);
QQueue<Dir> faitechemCombat(bool casemarchees[NBR_CASES_L] [NBR_CASES_H], QVector<QPoint>const& arrivees, QVector<UnChemin>parents, QPoint *arrivee);//on doit arriver à une des cases
QQueue<Dir> faitechem(bool casemarchees[NBR_CASES_L] [NBR_CASES_H], QPoint const& arr, QVector<UnChemin>parents);
QQueue<Dir> faitechem(bool casemarchees[NBR_CASES_L] [NBR_CASES_H], QVector<QPoint>const& arrivees, QVector<UnChemin>parents, QPoint *arrivee);//on doit arriver à une des cases
void case_suivante(int *x, int *y, Dir dir);
void case_suivante_simple(int *x, int *y, Dir dir);

void calculPortee(int cases_pleines[NBR_CASES_L] [NBR_CASES_H], bool cases_ateignables[NBR_CASES_L] [NBR_CASES_H], int xdep, int ydep, int max_portee);
void portee(int cases_intraversables[NBR_CASES_L] [NBR_CASES_H],bool cases_ateignables[NBR_CASES_L] [NBR_CASES_H], int xdep, int ydep, bool o, bool od, bool d, bool bd, bool b, bool bg, bool g, bool og, int max_portee);
void portee_aux(int cases_intraversables[NBR_CASES_L] [NBR_CASES_H], bool cases_ateignables[NBR_CASES_L] [NBR_CASES_H], int x, int y, bool adroite, bool agauche, Dir dir, int max_portee);

void portee2_aux(int cases_pleines[NBR_CASES_L] [NBR_CASES_H], bool cases_ateignables[NBR_CASES_L] [NBR_CASES_H], int xdep, int ydep, int max_portee, Dir dir);
void portee2(int cases_pleines[NBR_CASES_L] [NBR_CASES_H], bool cases_ateignables[NBR_CASES_L] [NBR_CASES_H], int xdep, int ydep, int max_portee);

bool caseExiste(int x, int y);

#endif // RECHERCHECHEMIN_H
