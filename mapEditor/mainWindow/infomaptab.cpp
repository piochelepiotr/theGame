#include "infomaptab.h"
#include "mainwindow.h"

InfoMapTab::InfoMapTab(MainWindow *mainWindow) :
    QWidget(mainWindow)
{
    m_layinfomap = new QVBoxLayout;
    setLayout(m_layinfomap);
    m_choixdufond = new QPushButton(trUtf8("charge le fond"));
    m_layinfomap->addWidget(m_choixdufond);
    m_monstresDeLaMap = new QPushButton(trUtf8("éditer les monstres de la map"));
    connect(m_monstresDeLaMap, SIGNAL(pressed()), mainWindow, SLOT(monstresDeLaMap()));
    m_layinfomap->addWidget(m_monstresDeLaMap);
    m_musiques = new QPushButton(trUtf8("éditer les musiques de la map"));
    connect(m_musiques, SIGNAL(pressed()), mainWindow, SLOT(musiques()));
    m_layinfomap->addWidget(m_musiques);

    connect(m_choixdufond, SIGNAL(clicked()), mainWindow, SLOT(chargefond()));

}
