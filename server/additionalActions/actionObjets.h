#ifndef ACTIONOBJETS_H
#define ACTIONOBJETS_H

#include <QString>
#include <QDir>
#include <QTextStream>
#include <QDataStream>
#include "elementsMonde/decors.h"
#include "additionalActions/constantes.h"

bool mapexiste(int x, int y, int z);
bool operator<(QPoint const &a, QPoint const& b);

qint16 trouveNumero();
bool chargeMap(Decors *decors, int cooX, int cooY, int cooZ, Objet *objets[3] [NBR_CASES_L] [NBR_CASES_H]);


#endif // ACTIONOBJETS_H
