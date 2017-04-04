#ifndef ACTIONOBJETS_H
#define ACTIONOBJETS_H

#include <QString>
#include <QDir>
#include <QTextStream>
#include <QDataStream>
#include "scenery/scenery.h"
#include "scenery/constants.h"
#include "map/gate.h"

bool operator<(QPoint const &a, QPoint const& b);
bool mapexiste(int x, int y, int z);

qint16 trouveNumero();
void ajouteUnTheme(QString const& nom);
void ajouteObjet(Object *objet, QString const& chemin_vers_image);
void sortUnObjet(Object *objet);
void enregistreMap(int cooX, int cooY, int cooZ,Object *objets[3] [NBR_CASES_L] [NBR_CASES_H], QMap <QPoint, Gate> const& transpos, qint8 casepleines[NBR_CASES_L] [NBR_CASES_H], QString fond, QPoint casescbt[2] [MAX_PAR_EQUIP], QMap<QString, double>monstres, QVector<QString>musiques, int undo = -1);
bool chargeMap(Scenery *decors, int cooX, int cooY, int cooZ, Object *objets[3] [NBR_CASES_L] [NBR_CASES_H], QMap <QPoint, Gate> & transpos, qint8 casepleines[NBR_CASES_L] [NBR_CASES_H], QString *fond, QPoint casescbt[2] [MAX_PAR_EQUIP], QMap<QString, double> * monstres, QVector<QString>*musiques, int undo = -1);
void supprimerObjet(Scenery *decors, Object *objet);


#endif // ACTIONOBJETS_H
