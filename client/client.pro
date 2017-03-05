QT += network
QT += widgets
QT += testlib

SOURCES += \
    main.cpp \
    additionalWindows/caracteristiques.cpp \
    additionalWindows/descriptionSort.cpp \
    additionalWindows/dialoguepnj.cpp \
    additionalWindows/echange.cpp \
    additionalWindows/fairerecettes.cpp \
    additionalWindows/interjoueur.cpp \
    graphicGame/actions_personnage.cpp \
    graphicGame/jeu_graphique.cpp \
    graphicGame/lejeu2d.cpp \
    mainWindow/fenprin.cpp \
    network/compte.cpp \
    network/reseau.cpp \
    graphicGame/objsurscene.cpp \
    graphicGame/affichejoueur.cpp \
    combats/combat.cpp \
    graphicGame/tooltip.cpp \
    additionalWindows/windowendfight.cpp \
    graphicGame/layoutbarreoutil.cpp

HEADERS += \
    additionalWindows/caracteristiques.h \
    additionalWindows/description_sort.h \
    additionalWindows/dialoguepnj.h \
    additionalWindows/echange.h \
    additionalWindows/fairerecettes.h \
    additionalWindows/interjoueur.h \
    graphicGame/actions_personnage.h \
    graphicGame/jeu_graphique.h \
    graphicGame/lejeu2d.h \
    mainWindow/fenprin.h \
    network/compte.h \
    network/reseau.h \
    graphicGame/objsurscene.h \
    graphicGame/affichejoueur.h \
    combats/combat.h \
    graphicGame/tooltip.h \
    additionalWindows/windowendfight.h \
    graphicGame/layoutbarreoutil.h

FORMS += \
    additionalWindows/caracteristiques.ui \
    additionalWindows/description_sort.ui \
    additionalWindows/echange.ui \
    additionalWindows/fairerecettes.ui \
    additionalWindows/interjoueur.ui \
    mainWindow/choixmainwindow.ui \
    mainWindow/comainwindow.ui \
    mainWindow/creermainwindow.ui \
    mainWindow/jeumainwindow.ui \
    additionalWindows/windowendfight.ui

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../build-gameLibrary-Desktop-Debug/release/ -lgameLibrary
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../build-gameLibrary-Desktop-Debug/debug/ -lgameLibrary
else:unix: LIBS += -L$$PWD/../build-gameLibrary-Desktop-Debug/ -lgameLibrary

INCLUDEPATH += $$PWD/../gameLibrary
DEPENDPATH += $$PWD/../gameLibrary
