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
    mainWindow/fenprin.cpp \
    network/compte.cpp \
    network/reseau.cpp \
    graphicGame/affichejoueur.cpp \
    combats/combat.cpp \
    additionalWindows/windowendfight.cpp \
    graphicGame/layoutbarreoutil.cpp \
    graphicGame/gamefield.cpp \
    additionalWindows/entityactions.cpp

HEADERS += \
    additionalWindows/caracteristiques.h \
    additionalWindows/dialoguepnj.h \
    additionalWindows/echange.h \
    additionalWindows/fairerecettes.h \
    additionalWindows/interjoueur.h \
    graphicGame/actions_personnage.h \
    mainWindow/fenprin.h \
    network/compte.h \
    network/reseau.h \
    graphicGame/affichejoueur.h \
    combats/combat.h \
    additionalWindows/windowendfight.h \
    graphicGame/layoutbarreoutil.h \
    graphicGame/gamefield.h \
    additionalWindows/entityactions.h

FORMS += \
    additionalWindows/caracteristiques.ui \
    additionalWindows/echange.ui \
    additionalWindows/fairerecettes.ui \
    additionalWindows/interjoueur.ui \
    mainWindow/choixmainwindow.ui \
    mainWindow/comainwindow.ui \
    mainWindow/creermainwindow.ui \
    mainWindow/jeumainwindow.ui \
    additionalWindows/windowendfight.ui

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../data-shared/release/ -lshared
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../data-shared/debug/ -lshared
else:unix: LIBS += -L$$PWD/../data-shared -lshared

INCLUDEPATH += $$PWD/../shared
DEPENDPATH += $$PWD/../shared
