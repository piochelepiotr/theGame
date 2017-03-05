#include "combatframestab.h"
#include "mainwindow.h"

CombatFramesTab::CombatFramesTab(MainWindow *mainWindow, Jeu2d *gamePanel) :
    QWidget(mainWindow)
{
    m_layCasesCombat = new QVBoxLayout;
    this->setLayout(m_layCasesCombat);
    m_groupCasesCbt = new QGroupBox(trUtf8("Cases combat de l'équipe :"));
    m_equipe_une = new QRadioButton("1");
    m_equipe_une->setChecked(true);
    m_equipe_deux = new QRadioButton("2");
    m_laycasescbt = new QHBoxLayout;
    m_laycasescbt->addWidget(m_equipe_une);
    m_laycasescbt->addWidget(m_equipe_deux);
    m_groupCasesCbt->setLayout(m_laycasescbt);
    m_layCasesCombat->addWidget(m_groupCasesCbt);

    connect(m_equipe_une, SIGNAL(pressed()), gamePanel, SLOT(equipe1()));
    connect(m_equipe_deux, SIGNAL(pressed()), gamePanel, SLOT(equipe2()));

}
