QT += widgets
QT += network
QT += sql

SOURCES += \
    main.cpp \
    graphic/ecran.cpp \
    monde/combat.cpp \
    monde/joueur.cpp \
    network/compte.cpp \
    network/database.cpp \
    monde/map.cpp \
    monde/monde.cpp

HEADERS += \
    graphic/ecran.h \
    monde/combat.h \
    monde/joueur.h \
    network/compte.h \
    network/database.h \
    monde/map.h \
    monde/monde.h

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../build-gameLibrary-Desktop-Debug/release/ -lgameLibrary
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../build-gameLibrary-Desktop-Debug/debug/ -lgameLibrary
else:unix: LIBS += -L$$PWD/../build-gameLibrary-Desktop-Debug/ -lgameLibrary

INCLUDEPATH += $$PWD/../gameLibrary
DEPENDPATH += $$PWD/../gameLibrary
