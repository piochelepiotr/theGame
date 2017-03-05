#ifndef CONSTANTES_H
#define CONSTANTES_H

#include <QString>
#include <QPoint>
#include <QDebug>

//emplacement des ressources

#define DOSSIER_IMAGES_SORTS "imagesSorts/"

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
#define NBR_CASES_L 25
#define NBR_CASES_H 51
#define CASESCACHEESX 3
#define CASESCACHEESY 6
#define NBR_IMAGES_SECONDE 20
#define MAX_PAR_EQUIP 15
#define ECART 1/5
#define DONNEES "donnees/"
#define NBR_LVL_SORTS 10
#define INTERVALE_RECETTE 1000
#define HAUTEUR_BARRE_OUTIL 70
#define FOND_DEFAUT "ogeante.png"

const double screenFormat = 1.7;

typedef struct InfoPerVis InfoPerVis;
struct InfoPerVis
{
    QString nom;
    QString classe;
    QPoint posmap;
};

enum Dir{O,OG,G,BG,B,BD,D,OD};

//qRegisterMetaType<Dir>("Dir");
//qRegisterMetaType<struct InfoPerVis>("InfoPerVis");

#endif // CONSTANTES_H
