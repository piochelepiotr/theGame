#include "objectstab.h"
#include "mainwindow.h"

ObjectsTab::ObjectsTab(MainWindow *mainWindow, Jeu2d *gamePanel) :
    QWidget(mainWindow)
{
    m_objets = new QVBoxLayout;
    m_hautobjets = new QHBoxLayout;
    m_themesObjet = new QComboBox;
    m_themesObjet->addItems(gamePanel->decors()->categories());
    m_ajouterUnThemeObjet = new QPushButton(trUtf8("Ajouter un thème"));
    m_ajouterUnObjet = new QPushButton(trUtf8("Ajouter un objet au thème"));
    m_effaceurobjet = new QPushButton(trUtf8("effaceur"));
    m_remplire = new QPushButton(trUtf8("remplir"));
    m_bout_editobj = new QPushButton(trUtf8("spell"));
    m_lay_bas_objets = new QHBoxLayout();
    m_lay_imagesObjets = new QHBoxLayout;
    m_scroll_imagesObjets = new QScrollArea();
    m_scroll_imagesObjets->setWidgetResizable(true);
    m_scroll_imagesObjets->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    m_wid_imagesObjets = new QWidget;
    m_lay_actions_objet = new QVBoxLayout;
    m_lay_actions_objet->addWidget(m_effaceurobjet);
    m_lay_actions_objet->addWidget(m_remplire);
    m_lay_actions_objet->addWidget(m_bout_editobj);
    m_lay_bas_objets->addLayout(m_lay_actions_objet);
    m_wid_imagesObjets->setLayout(m_lay_imagesObjets);
    m_scroll_imagesObjets->setWidget(m_wid_imagesObjets);
    m_lay_bas_objets->addWidget(m_scroll_imagesObjets);
    m_scroll_imagesObjets->setMinimumHeight(150);
    //mainWindow->chargeThemeObjet(0);
    m_hautobjets->addWidget(m_themesObjet);
    m_hautobjets->addWidget(m_ajouterUnThemeObjet);
    m_hautobjets->addWidget(m_ajouterUnObjet);
    m_objets->addLayout(m_hautobjets);
    m_objets->addLayout(m_lay_bas_objets);
    setLayout(m_objets);
    m_groupCalc = new QGroupBox(trUtf8("calc"));
    m_calcObject = new QRadioButton("Objects");
    m_calcObject->setChecked(true);
    m_calcBackground = new QRadioButton("Background");
    m_laycalc = new QHBoxLayout;
    m_laycalc->addWidget(m_calcObject);
    m_laycalc->addWidget(m_calcBackground);
    m_groupCalc->setLayout(m_laycalc);
    m_hautobjets->addWidget(m_groupCalc);

    connect(m_calcObject, SIGNAL(pressed()), gamePanel, SLOT(calcObject()));
    connect(m_calcBackground, SIGNAL(pressed()), gamePanel, SLOT(calcBacground()));
    connect(m_remplire, SIGNAL(clicked()), gamePanel, SLOT(remplire()));
    connect(m_ajouterUnThemeObjet, SIGNAL(clicked()), mainWindow, SLOT(nouveauThemeObjet()));
    connect(m_ajouterUnObjet, SIGNAL(clicked()), mainWindow, SLOT(nouveauObjetPourTheme()));
    connect(m_themesObjet, SIGNAL(currentIndexChanged(int)), mainWindow, SLOT(chargeThemeObjet(int)));
    connect(m_effaceurobjet, SIGNAL(clicked()), mainWindow, SLOT(selectionNouveauObjet()));
    connect(m_bout_editobj, SIGNAL(clicked()), mainWindow, SLOT(spellObjet()));

}
