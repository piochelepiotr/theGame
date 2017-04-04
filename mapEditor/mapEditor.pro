QT += widgets

SOURCES += \
    main.cpp \
    mainWindow/addtoworldtab.cpp \
    mainWindow/bottomtab.cpp \
    mainWindow/boutonimg.cpp \
    mainWindow/fightframestab.cpp \
    mainWindow/infomaptab.cpp \
    mainWindow/jeu2d.cpp \
    mainWindow/mainwindow.cpp \
    mainWindow/objectstab.cpp \
    mainWindow/varioustab.cpp \
    mainWindow/walkableframestab.cpp \
    mainWindow/buttonobject.cpp \
    additionalWindows/createmonsterresource.cpp \
    additionalWindows/createnpc.cpp \
    additionalWindows/editclasses.cpp \
    additionalWindows/editentity.cpp \
    additionalWindows/editgate.cpp \
    additionalWindows/editjob.cpp \
    additionalWindows/editmapmonsters.cpp \
    additionalWindows/editmonsters.cpp \
    additionalWindows/editmusics.cpp \
    additionalWindows/editnpcs.cpp \
    additionalWindows/editobject.cpp \
    additionalWindows/editresources.cpp \
    additionalWindows/editspell.cpp \
    additionalWindows/editspells.cpp

HEADERS += \
    mainWindow/addtoworldtab.h \
    mainWindow/bottomtab.h \
    mainWindow/boutonimg.h \
    mainWindow/fightframestab.h \
    mainWindow/infomaptab.h \
    mainWindow/jeu2d.h \
    mainWindow/mainwindow.h \
    mainWindow/objectstab.h \
    mainWindow/varioustab.h \
    mainWindow/walkableframestab.h \
    mainWindow/buttonobject.h \
    additionalWindows/createmonsterresource.h \
    additionalWindows/createnpc.h \
    additionalWindows/editclasses.h \
    additionalWindows/editentity.h \
    additionalWindows/editgate.h \
    additionalWindows/editjob.h \
    additionalWindows/editmapmonsters.h \
    additionalWindows/editmonsters.h \
    additionalWindows/editmusics.h \
    additionalWindows/editnpcs.h \
    additionalWindows/editobject.h \
    additionalWindows/editresources.h \
    additionalWindows/editspell.h \
    additionalWindows/editspells.h

FORMS += \
    mainWindow/mainwindow.ui \
    additionalWindows/createmonsterresource.ui \
    additionalWindows/createnpc.ui \
    additionalWindows/editclasses.ui \
    additionalWindows/editentity.ui \
    additionalWindows/editgate.ui \
    additionalWindows/editjob.ui \
    additionalWindows/editmapmonsters.ui \
    additionalWindows/editmonsters.ui \
    additionalWindows/editmusics.ui \
    additionalWindows/editnpcs.ui \
    additionalWindows/editobject.ui \
    additionalWindows/editresources.ui \
    additionalWindows/editspell.ui \
    additionalWindows/editspells.ui

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../data-shared/release/ -lshared
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../data-shared/debug/ -lshared
else:unix: LIBS += -L$$PWD/../data-shared -lshared

INCLUDEPATH += $$PWD/../shared
DEPENDPATH += $$PWD/../shared
