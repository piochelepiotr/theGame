#ifndef ACTIONOBJETS_H
#define ACTIONOBJETS_H

#include <QString>
#include <QDir>
#include <QTextStream>
#include <QDataStream>
#include "scenery/scenery.h"
#include "scenery/constants.h"
#include "map/gate.h"

qint16 trouveNumero();
void ajouteUnTheme(QString const& name);
void ajouteObjet(Object *objet, QString const& chemin_vers_image);
void editAnObject(Object *objet);
void supprimerObjet(Scenery *decors, Object *objet);


#endif // ACTIONOBJETS_H
