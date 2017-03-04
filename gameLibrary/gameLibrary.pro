#-------------------------------------------------
#
# Project created by QtCreator 2015-11-18T16:41:24
#
#-------------------------------------------------

QT       += widgets network sql

QT       -= gui

TARGET = gameLibrary
TEMPLATE = lib

DEFINES += GAMELIBRARY_LIBRARY

SOURCES += \
    infoJoueur/arme.cpp \
    infoJoueur/equipement.cpp \
    infoJoueur/inventaire.cpp \
    infoJoueur/metier.cpp \
    infoJoueur/personnage.cpp \
    infoJoueur/sort.cpp \
    elementsMonde/categorie.cpp \
    elementsMonde/decors.cpp \
    elementsMonde/donnees_editeur.cpp \
    elementsMonde/objet_coupable.cpp \
    elementsMonde/objet.cpp \
    elementsMonde/touslesmetiers.cpp \
    elementsMonde/touslespnj.cpp \
    elementsMonde/transporteur.cpp \
    infoMonde/armebase.cpp \
    infoMonde/classe.cpp \
    infoMonde/creature.cpp \
    infoMonde/equipementbase.cpp \
    infoMonde/images_classe.cpp \
    infoMonde/lesressources.cpp \
    infoMonde/metier_base.cpp \
    infoMonde/monstre.cpp \
    infoMonde/persnonj.cpp \
    infoMonde/recette.cpp \
    infoMonde/recettes.cpp \
    infoMonde/ressource.cpp \
    infoMonde/unecreature.cpp \
    infoMonde/unmonstre.cpp \
    infoMonde/unsort.cpp \
    graphicElements/gainunpersocombat.cpp \
    graphicElements/item.cpp \
    graphicElements/items.cpp \
    graphicElements/layoutdescriptionsort.cpp \
    graphicElements/layoutunsort.cpp \
    graphicElements/descriptionSort.cpp \
    additionalActions/actionObjets.cpp \
    additionalActions/datamap.cpp \
    additionalActions/point.cpp \
    additionalActions/rechercheChemin.cpp \
    additionalActions/unchemin.cpp \
    graphicElements/bouton.cpp \
    graphicElements/boutonimgString.cpp

HEADERS += \
    infoJoueur/arme.h \
    infoJoueur/equipement.h \
    infoJoueur/inventaire.h \
    infoJoueur/metier.h \
    infoJoueur/personnage.h \
    infoJoueur/sort.h \
    elementsMonde/categorie.h \
    elementsMonde/decors.h \
    elementsMonde/donnees_editeur.h \
    elementsMonde/objet_coupable.h \
    elementsMonde/objet.h \
    elementsMonde/touslesmetiers.h \
    elementsMonde/touslespnj.h \
    elementsMonde/transporteur.h \
    infoMonde/armebase.h \
    infoMonde/classe.h \
    infoMonde/creature.h \
    infoMonde/equipementbase.h \
    infoMonde/images_classe.h \
    infoMonde/lesressources.h \
    infoMonde/metier_base.h \
    infoMonde/monstre.h \
    infoMonde/persnonj.h \
    infoMonde/recette.h \
    infoMonde/recettes.h \
    infoMonde/ressource.h \
    infoMonde/unecreature.h \
    infoMonde/unmonstre.h \
    infoMonde/unsort.h \
    graphicElements/gainunpersocombat.h \
    graphicElements/item.h \
    graphicElements/items.h \
    graphicElements/layoutdescriptionsort.h \
    graphicElements/layoutunsort.h \
    graphicElements/description_sort.h \
    additionalActions/actionObjets.h \
    additionalActions/constantes.h \
    additionalActions/datamap.h \
    additionalActions/point.h \
    additionalActions/rechercheChemin.h \
    additionalActions/unchemin.h \
    graphicElements/bouton.h \
    graphicElements/boutonimgString.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}

FORMS += \
    graphicElements/description_sort.ui
