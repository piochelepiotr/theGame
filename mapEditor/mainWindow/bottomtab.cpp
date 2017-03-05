#include "bottomtab.h"
#include "mainwindow.h"

BottomTab::BottomTab(MainWindow *mainWindow, Jeu2d *gamePanel, LesRessources *ressources) :
    QTabWidget(mainWindow)
{
    m_widdivers = new VariousTab(mainWindow);
    addTab(m_widdivers, trUtf8("général"));
    m_widinfomap = new InfoMapTab(mainWindow);
    addTab(m_widinfomap, trUtf8("info map"));
    m_widobjets = new ObjectsTab(mainWindow,gamePanel);
    addTab(m_widobjets, trUtf8("Les objets"));//un truc a faire ici
    m_widCasesMarchables = new walkableFramesTab(mainWindow,gamePanel);
    addTab(m_widCasesMarchables, trUtf8("Cases marchables"));
    m_widCasesCombat = new CombatFramesTab(mainWindow,gamePanel);
    addTab(m_widCasesCombat, "Cases combat");
    m_widajouteMonde = new AddToWorldTab(mainWindow,gamePanel,ressources);
    addTab(m_widajouteMonde, trUtf8("ajoute au monde"));
}

