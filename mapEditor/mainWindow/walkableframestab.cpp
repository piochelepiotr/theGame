#include "walkableframestab.h"
#include "mainwindow.h"

walkableFramesTab::walkableFramesTab(MainWindow *mainWindow, Jeu2d *gamePanel) :
    QWidget(mainWindow)
{
    m_layCasesMarchables = new QVBoxLayout;
    this->setLayout(m_layCasesMarchables);
    m_groupTaille = new QGroupBox(trUtf8("plage cases marchables"));
    m_un = new QRadioButton(trUtf8("petit"));
    m_un->setChecked(true);
    m_trois = new QRadioButton(trUtf8("moyen"));
    m_cinq = new QRadioButton(trUtf8("grand"));
    m_laytaille = new QHBoxLayout;
    m_laytaille->addWidget(m_un);
    m_laytaille->addWidget(m_trois);
    m_laytaille->addWidget(m_cinq);
    m_groupTaille->setLayout(m_laytaille);
    m_layCasesMarchables->addWidget(m_groupTaille);

    connect(m_un, SIGNAL(pressed()), gamePanel, SLOT(tailleun()));
    connect(m_trois, SIGNAL(pressed()), gamePanel, SLOT(tailletrois()));
    connect(m_cinq, SIGNAL(pressed()), gamePanel, SLOT(taillecinq()));
}
