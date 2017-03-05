#ifndef BOTTOMTAB_H
#define BOTTOMTAB_H

#include <QTabWidget>
#include "mainWindow/addtoworldtab.h"
#include "mainWindow/combatframestab.h"
#include "mainWindow/infomaptab.h"
#include "mainWindow/objectstab.h"
#include "mainWindow/varioustab.h"
#include "mainWindow/walkableframestab.h"


class MainWindow;
class Jeu2d;


class BottomTab : public QTabWidget
{
    Q_OBJECT
public:
    explicit BottomTab(MainWindow *mainWindow,Jeu2d *gamePanel, LesRessources *ressources);

    VariousTab *m_widdivers;
    ObjectsTab *m_widobjets;
    InfoMapTab *m_widinfomap;
    walkableFramesTab *m_widCasesMarchables;
    CombatFramesTab *m_widCasesCombat;
    AddToWorldTab *m_widajouteMonde;

signals:

public slots:

};

#endif // BOTTOMTAB_H
