#-------------------------------------------------
#
# Project created by QtCreator 2015-11-18T16:41:24
#
#-------------------------------------------------

QT       += widgets network sql

QT       -= gui

TARGET = shared
TEMPLATE = lib

DEFINES += SHARED_LIBRARY

SOURCES += \
    entities/character.cpp \
    entities/characterModel.cpp \
    entities/entity.cpp \
    entities/entityImage.cpp \
    entities/entityModel.cpp \
    entities/monster.cpp \
    entities/monsterModel.cpp \
    entities/npc.cpp \
    entities/npcs.cpp \
    entities/spell.cpp \
    entities/spellModel.cpp \
    graphic/fightWinnings.cpp \
    graphic/gamescene.cpp \
    graphic/imageButton.cpp \
    graphic/numberButton.cpp \
    graphic/objectItem.cpp \
    graphic/resourceItem.cpp \
    graphic/resourceItems.cpp \
    graphic/spellDescritionLayout.cpp \
    graphic/spellDescritpion.cpp \
    graphic/spellLayout.cpp \
    graphic/toolBarLayout.cpp \
    inventory/inventory.cpp \
    inventory/outfit.cpp \
    inventory/outfitModel.cpp \
    inventory/resource.cpp \
    inventory/resources.cpp \
    inventory/weapon.cpp \
    inventory/weaponModel.cpp \
    jobs/interactiveObject.cpp \
    jobs/job.cpp \
    jobs/jobModel.cpp \
    jobs/jobs.cpp \
    jobs/recipe.cpp \
    jobs/recipes.cpp \
    map/computePath.cpp \
    map/gate.cpp \
    map/map.cpp \
    map/path.cpp \
    map/point.cpp \
    scenery/data.cpp \
    scenery/object.cpp \
    scenery/objectGroup.cpp \
    scenery/scenery.cpp \
    scenery/sceneryChange.cpp

HEADERS += \
    entities/character.h \
    entities/characterModel.h \
    entities/entity.h \
    entities/entityImage.h \
    entities/entityModel.h \
    entities/monster.h \
    entities/monsterModel.h \
    entities/npc.h \
    entities/npcs.h \
    entities/spell.h \
    entities/spellModel.h \
    graphic/fightWinning.h \
    graphic/gamescene.h \
    graphic/imageButton.h \
    graphic/numberButton.h \
    graphic/objectItem.h \
    graphic/resourceItem.h \
    graphic/resourceItems.h \
    graphic/spellDescription.h \
    graphic/spellDescriptionLayout.h \
    graphic/spellLayout.h \
    graphic/toolBarLayout.h \
    inventory/inventory.h \
    inventory/outfit.h \
    inventory/outfitModel.h \
    inventory/resource.h \
    inventory/resources.h \
    inventory/weapon.h \
    inventory/weaponModel.h \
    jobs/interactiveObject.h \
    jobs/job.h \
    jobs/jobModel.h \
    jobs/jobs.h \
    jobs/recipe.h \
    jobs/recipes.h \
    map/computePath.h \
    map/gate.h \
    map/map.h \
    map/path.h \
    map/point.h \
    scenery/constants.h \
    scenery/data.h \
    scenery/object.h \
    scenery/objectGroup.h \
    scenery/scenery.h \
    scenery/sceneryChange.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}

FORMS += \
    graphic/spellDescription.ui

