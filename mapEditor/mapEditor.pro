QT += widgets

SOURCES += \
    main.cpp \
    additionalWindows/creerpnj.cpp \
    additionalWindows/editerclasses.cpp \
    additionalWindows/editermetier.cpp \
    additionalWindows/editermonstredelamap.cpp \
    additionalWindows/editermonstres.cpp \
    additionalWindows/editermusiques.cpp \
    additionalWindows/editerpnjs.cpp \
    additionalWindows/editerressources.cpp \
    additionalWindows/editersorts.cpp \
    additionalWindows/editertransporteur.cpp \
    additionalWindows/editerunobjet.cpp \
    additionalWindows/editerunsort.cpp \
    mainWindow/addtoworldtab.cpp \
    mainWindow/bottomtab.cpp \
    mainWindow/boutonimg.cpp \
    mainWindow/combatframestab.cpp \
    mainWindow/infomaptab.cpp \
    mainWindow/jeu2d.cpp \
    mainWindow/mainwindow.cpp \
    mainWindow/objectstab.cpp \
    mainWindow/varioustab.cpp \
    mainWindow/walkableframestab.cpp \
    additionalWindows/editercreature.cpp \
    additionalWindows/nouvelleressourcemonstre.cpp

HEADERS += \
    additionalWindows/creerpnj.h \
    additionalWindows/editerclasses.h \
    additionalWindows/editermetier.h \
    additionalWindows/editermonstredelamap.h \
    additionalWindows/editermonstres.h \
    additionalWindows/editermusiques.h \
    additionalWindows/editerpnjs.h \
    additionalWindows/editerressources.h \
    additionalWindows/editersorts.h \
    additionalWindows/editertransporteur.h \
    additionalWindows/editerunobjet.h \
    additionalWindows/editerunsort.h \
    mainWindow/addtoworldtab.h \
    mainWindow/bottomtab.h \
    mainWindow/boutonimg.h \
    mainWindow/combatframestab.h \
    mainWindow/infomaptab.h \
    mainWindow/jeu2d.h \
    mainWindow/mainwindow.h \
    mainWindow/objectstab.h \
    mainWindow/varioustab.h \
    mainWindow/walkableframestab.h \
    additionalWindows/editercreature.h \
    additionalWindows/nouvelleressourcemonstre.h

FORMS += \
    additionalWindows/creerpnj.ui \
    additionalWindows/editerclasses.ui \
    additionalWindows/editermetier.ui \
    additionalWindows/editermonstredelamap.ui \
    additionalWindows/editermonstres.ui \
    additionalWindows/editermusiques.ui \
    additionalWindows/editerpnjs.ui \
    additionalWindows/editerressources.ui \
    additionalWindows/editersorts.ui \
    additionalWindows/editertransporteur.ui \
    additionalWindows/editerunobjet.ui \
    additionalWindows/editerunsort.ui \
    mainWindow/mainwindow.ui \
    additionalWindows/editercreature.ui \
    additionalWindows/nouvelleressourcemonstre.ui

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../data-shared/release/ -lshared
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../data-shared/debug/ -lshared
else:unix: LIBS += -L$$PWD/../data-shared -lshared

INCLUDEPATH += $$PWD/../shared
DEPENDPATH += $$PWD/../shared
