#ifndef CONSTANTES_H
#define CONSTANTES_H

#include <QtDebug>
#include <QObject>

//editeur

#define CALQUE_DEFAUT 2

#define NBR_LVL_SORTS 10

#define SORT_DEFAUT QObject::trUtf8("Coup de poing")

//jeu

#define NBR_DE_MAPS_X 8
#define NBR_DE_MAPS_Y 5
#define NBR_DE_MAPS_Z 5
#define MAX_CHEMIN 100
#define NBR_CASES_L 25
#define NBR_CASES_H 51
#define CASESCACHEESX 3
#define CASESCACHEESY 6
#define NBR_IMAGES_SECONDE 6
#define MAX_PAR_EQUIP 15
#define ECART 1/5
#define DONNEES "donnees/"
#define FOND_DEFAUT "ogeante.png"

enum Dir{O,OG,G,BG,B,BD,D,OD};

#endif // CONSTANTES_H
