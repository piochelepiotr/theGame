#include "addtoworldtab.h"
#include "mainwindow.h"

AddToWorldTab::AddToWorldTab(MainWindow *mainWindow, Jeu2d *gamePanel, Resources *resources) :
    QWidget(mainWindow)
{
    m_resources = resources;
    m_jeu = gamePanel;
    m_mainWindow = mainWindow;
    m_layajouteMonde = new QGridLayout;
    m_editeRessources = new QPushButton(trUtf8("Editer les resources"));
    m_editePnj = new QPushButton(trUtf8("Editer les personnages non joueur"));
    m_editeMetiers = new QPushButton(trUtf8("Editer les métiers"));
    m_editeMonstres = new QPushButton(trUtf8("Editer les monstres"));
    m_editeSpells = new QPushButton(trUtf8("Editer les spells"));
    m_editeClasses = new QPushButton(trUtf8("Editer les classes"));
    this->setLayout(m_layajouteMonde);
    m_layajouteMonde->addWidget(m_editeRessources, 0,0);
    m_layajouteMonde->addWidget(m_editePnj, 1,0);
    m_layajouteMonde->addWidget(m_editeMetiers, 2, 0);
    m_layajouteMonde->addWidget(m_editeMonstres, 0, 1);
    m_layajouteMonde->addWidget(m_editeSpells, 1, 1);
    m_layajouteMonde->addWidget(m_editeClasses, 2, 1);
    connect(m_editeMetiers, SIGNAL(clicked()), this, SLOT(editeMetiers()));
    connect(m_editeMonstres, SIGNAL(clicked()), this, SLOT(editeMonstres()));
    connect(m_editeSpells, SIGNAL(clicked()), this, SLOT(editeSpells()));
    connect(m_editeClasses, SIGNAL(clicked()), this, SLOT(editeClasses()));
    connect(m_editeRessources, SIGNAL(clicked()), this, SLOT(spellRessources()));
    connect(m_editePnj, SIGNAL(clicked()), this, SLOT(spellPnjs()));

}

void AddToWorldTab::editeMetiers()
{
    EditerMetier boite(m_mainWindow, m_jeu->decors(), m_resources);
}

void AddToWorldTab::editeMonstres()
{
    EditerMonstres boite(m_mainWindow,m_resources);
}

void AddToWorldTab::editeSpells()
{
    EditerSpells boite(m_mainWindow, m_resources);
}

void AddToWorldTab::editeClasses()
{
    EditerClasses boite(m_mainWindow);
}

void AddToWorldTab::spellRessources()
{
    EditerRessources boite(m_mainWindow, m_resources);
}

void AddToWorldTab::spellPnjs()
{
    EditerPnjs boite(m_mainWindow, m_jeu->decors());
}




