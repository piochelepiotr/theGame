#include "addtoworldtab.h"
#include "mainwindow.h"

AddToWorldTab::AddToWorldTab(MainWindow *mainWindow, Jeu2d *gamePanel, Resources *ressources) :
    QWidget(mainWindow)
{
    m_ressources = ressources;
    m_jeu = gamePanel;
    m_mainWindow = mainWindow;
    m_layajouteMonde = new QGridLayout;
    m_editeRessources = new QPushButton(trUtf8("Editer les ressources"));
    m_editePnj = new QPushButton(trUtf8("Editer les personnages non joueur"));
    m_editeMetiers = new QPushButton(trUtf8("Editer les métiers"));
    m_editeMonstres = new QPushButton(trUtf8("Editer les monstres"));
    m_editeSorts = new QPushButton(trUtf8("Editer les sorts"));
    m_editeClasses = new QPushButton(trUtf8("Editer les classes"));
    this->setLayout(m_layajouteMonde);
    m_layajouteMonde->addWidget(m_editeRessources, 0,0);
    m_layajouteMonde->addWidget(m_editePnj, 1,0);
    m_layajouteMonde->addWidget(m_editeMetiers, 2, 0);
    m_layajouteMonde->addWidget(m_editeMonstres, 0, 1);
    m_layajouteMonde->addWidget(m_editeSorts, 1, 1);
    m_layajouteMonde->addWidget(m_editeClasses, 2, 1);
    connect(m_editeMetiers, SIGNAL(clicked()), this, SLOT(editeMetiers()));
    connect(m_editeMonstres, SIGNAL(clicked()), this, SLOT(editeMonstres()));
    connect(m_editeSorts, SIGNAL(clicked()), this, SLOT(editeSorts()));
    connect(m_editeClasses, SIGNAL(clicked()), this, SLOT(editeClasses()));
    connect(m_editeRessources, SIGNAL(clicked()), this, SLOT(sortRessources()));
    connect(m_editePnj, SIGNAL(clicked()), this, SLOT(sortPnjs()));

}

void AddToWorldTab::editeMetiers()
{
    EditerMetier boite(m_mainWindow, m_jeu->decors(), m_ressources);
}

void AddToWorldTab::editeMonstres()
{
    EditerMonstres boite(m_mainWindow,m_ressources);
}

void AddToWorldTab::editeSorts()
{
    EditerSorts boite(m_mainWindow, m_ressources);
}

void AddToWorldTab::editeClasses()
{
    EditerClasses boite(m_mainWindow);
}

void AddToWorldTab::sortRessources()
{
    EditerRessources boite(m_mainWindow, m_ressources);
}

void AddToWorldTab::sortPnjs()
{
    EditerPnjs boite(m_mainWindow, m_jeu->decors());
}




