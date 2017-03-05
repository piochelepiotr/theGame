#ifndef ACTIONOBJETS_H
#define ACTIONOBJETS_H

#include <QString>
#include <QDir>
#include <QTextStream>
#include <QDataStream>
#include "elementsMonde/decors.h"
#include "additionalActions/constantes.h"
#include "elementsMonde/transporteur.h"

bool operator<(QPoint const &a, QPoint const& b);
bool mapexiste(int x, int y, int z);

qint16 trouveNumero();
void ajouteUnTheme(QString const& nom);
void ajouteObjet(Objet *objet, QString const& chemin_vers_image);
void editerUnObjet(Objet *objet);
void enregistreMap(int cooX, int cooY, int cooZ,Objet *objets[3] [NBR_CASES_L] [NBR_CASES_H], QMap <QPoint, Transporteur> const& transpos, qint8 casepleines[NBR_CASES_L] [NBR_CASES_H], QString fond, QPoint casescbt[2] [MAX_PAR_EQUIP], QMap<QString, double>monstres, QVector<QString>musiques, int undo = -1);
bool chargeMap(Decors *decors, int cooX, int cooY, int cooZ, Objet *objets[3] [NBR_CASES_L] [NBR_CASES_H], QMap <QPoint, Transporteur> & transpos, qint8 casepleines[NBR_CASES_L] [NBR_CASES_H], QString *fond, QPoint casescbt[2] [MAX_PAR_EQUIP], QMap<QString, double> * monstres, QVector<QString>*musiques, int undo = -1);
void supprimerObjet(Decors *decors, Objet *objet);


#endif // ACTIONOBJETS_H
