#include "varioustab.h"
#include "mainwindow.h"

VariousTab::VariousTab(MainWindow *mainWindow) :
    QWidget(mainWindow)
{
    m_lay_divers = new QVBoxLayout();
    setLayout(m_lay_divers);
    m_charger_contour = new QPushButton("charger les contours");
    m_lay_divers->addWidget(m_charger_contour);
    m_groupzoom = new QGroupBox(trUtf8("zoom"));
    m_vue_large = new QRadioButton("non");
    m_vue_large->setChecked(true);
    m_vue_reduite = new QRadioButton("oui");
    m_layzoom = new QHBoxLayout;
    m_layzoom->addWidget(m_vue_large);
    m_layzoom->addWidget(m_vue_reduite);
    m_groupzoom->setLayout(m_layzoom);
    m_lay_divers->addWidget(m_groupzoom);

    m_groupoutils = new QGroupBox(trUtf8("outil"));
    m_outil_objets = new QRadioButton("objets");
    m_outil_objets->setChecked(true);
    m_outil_transporteurs = new QRadioButton("transporteurs");
    m_outil_cases_marchables = new QRadioButton("cases marchables");
    m_outil_casescbt = new QRadioButton("cases fight");
    m_outil_casespo = new QRadioButton(trUtf8("cases porté(e)"));
    m_layout_outils = new QHBoxLayout;
    m_layout_outils->addWidget(m_outil_objets);
    m_layout_outils->addWidget(m_outil_transporteurs);
    m_layout_outils->addWidget(m_outil_cases_marchables);
    m_layout_outils->addWidget(m_outil_casescbt);
    m_layout_outils->addWidget(m_outil_casespo);
    m_groupoutils->setLayout(m_layout_outils);
    m_lay_divers->addWidget(m_groupoutils);

    connect(m_outil_casespo, SIGNAL(clicked()), mainWindow, SLOT(outil_cases_po()));
    connect(m_charger_contour, SIGNAL(clicked()), mainWindow, SLOT(charger_contours()));
    connect(m_vue_large, SIGNAL(pressed()), mainWindow, SLOT(changeZoom()));
    connect(m_vue_reduite, SIGNAL(pressed()), mainWindow, SLOT(changeZoom()));
    connect(m_outil_objets, SIGNAL(pressed()), mainWindow, SLOT(outil_objets()));
    connect(m_outil_transporteurs, SIGNAL(pressed()), mainWindow, SLOT(outil_transporteurs()));
    connect(m_outil_cases_marchables, SIGNAL(pressed()), mainWindow, SLOT(outil_cases_marchables()));
    connect(m_outil_casescbt, SIGNAL(pressed()), mainWindow, SLOT(outil_cases_fight()));
}
