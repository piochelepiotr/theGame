QT += widgets
QT += network
QT += sql

SOURCES += \
    main.cpp \
    graphic/ecran.cpp \
    monde/joueur.cpp \
    network/compte.cpp \
    network/database.cpp \
    monde/map.cpp \
    monde/monde.cpp \
    monde/fight.cpp

HEADERS += \
    graphic/ecran.h \
    monde/joueur.h \
    network/compte.h \
    network/database.h \
    monde/map.h \
    monde/monde.h \
    monde/fight.h

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../data-shared/release/ -lshared
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../data-shared/debug/ -lshared
else:unix: LIBS += -L$$PWD/../data-shared -lshared

INCLUDEPATH += $$PWD/../shared
DEPENDPATH += $$PWD/../shared
