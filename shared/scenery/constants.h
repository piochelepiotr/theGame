#ifndef CONSTANTES_H
#define CONSTANTES_H

#include <QString>
#include <QPoint>
#include <QDebug>

//map editor

#define CALQUE_DEFAUT 2
#define NBR_LVL_SORTS 10
#define SORT_DEFAUT QObject::trUtf8("Coup de poing")

//server

#define TEMPS_MIN_REPOUSSE 60000
#define TEMPS_MAX_REPOUSSE 120000
#define METIER_LVLS_1CASEENPLUS 15

//emplacement des resources

#define DOSSIER_IMAGES_SORTS "../data/imagesSpells/"

//général

#define PORT 32001

//choix perso

#define PLPERSOCHOIX 1/3
#define PHPERSOCHOIX 5/6

//création perso

#define PLPERSOCREER 1/3
#define PHPERSOCREER 1/2


//inventaire

#define NBRRESSH 4
#define NBRRESSV 10


//jeu

#define NBR_DE_MAPS_X 8
#define NBR_DE_MAPS_Y 5
#define NBR_DE_MAPS_Z 5
#define MAX_CHEMIN 100
#define NBR_CASES_L 30
#define NBR_CASES_H 60
#define CASESCACHEESX 3
#define CASESCACHEESY 6
#define MAX_PAR_EQUIP 15
#define ECART 1/5
#define DONNEES "../data/donnees/"
#define NBR_LVL_SORTS 10
#define INTERVALE_RECETTE 1000
#define HAUTEUR_BARRE_OUTIL 70
#define FOND_DEFAUT "ogeante.png"

const double screenFormat = 1.7;

typedef struct EntityInfo EntityInfo;
struct EntityInfo
{
    QString name;
    QString classe;
    QPoint posmap;
    bool monster;
};

enum Dir{O,OG,G,BG,B,BD,D,OD};

//qRegisterMetaType<Dir>("Dir");

#endif // CONSTANTES_H
