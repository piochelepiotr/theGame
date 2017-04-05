#include "layoutbarreoutil.h"
#include "mainWindow/fenprin.h"

LayoutBarreOutil::LayoutBarreOutil(FenPrin *parent,Character *perso) :
    QHBoxLayout(parent)
{
    m_parent = parent;
    m_chat = new QListWidget;
    m_bar_chat = new QLineEdit;
    m_lay_chat = new QVBoxLayout;
    m_bout_cara = new QPushButton;
    m_bout_passer_tour = new QPushButton("Passer");
    m_bar_vie = new QProgressBar;
    m_lay_spells = new QHBoxLayout;
    m_bout_cac = new ImageButtonString("cac",QString(DOSSIER_IMAGES_SORTS)+QString("cac.png"));
    m_bout_cac->setToolTip(Spell::decrit(perso->getSpell("cac")));
    m_labelPC = new QLabel(QString::number(perso->getTotalPC()));

    m_lay_spells->addWidget(m_bout_cac);
    m_bout_cara->setIcon(QIcon("../data/interface/bouton.png"));
    m_bout_cara->setIconSize(QSize(50,50));
    m_lay_chat->addWidget(m_chat);
    m_lay_chat->addWidget(m_bar_chat);
    addLayout(m_lay_chat);
    addWidget(m_bout_cara);
    addWidget(m_bar_vie);
    addWidget(m_labelPC);
    addWidget(m_bout_passer_tour);
    addLayout(m_lay_spells);

    m_bar_vie->setMaximum(m_parent->getJeu()->getPerso()->getTotalVie());
    m_bar_vie->setValue(m_parent->getJeu()->getPerso()->getVie());
    m_bar_vie->setFormat("%v/%m");

    connect(m_bout_passer_tour, SIGNAL(clicked()), m_parent, SLOT(je_passe_tour()));
    connect(m_bout_cac, SIGNAL(clique(QString)), m_parent, SLOT(utiliseSpell(QString)));
    connect(m_bout_cara, SIGNAL(pressed()), m_parent, SLOT(caracteristiques()));
    connect(m_bar_chat, SIGNAL(returnPressed()), m_parent, SLOT(envoiAChat()));

    QMap<QString,Spell*>spells = perso->spells();
    ImageButtonString *bout = 0;
    for(QMap<QString,Spell*>::iterator it = spells.begin(); it != spells.end(); it++)
    {
        bout = new ImageButtonString(it.key(),QString(DOSSIER_IMAGES_SORTS)+it.key()+QString(".png"));
        bout->setToolTip(Spell::decrit(it.value()));
        connect(bout,SIGNAL(clique(QString)),m_parent,SLOT(utiliseSpell(QString)));
        m_lay_spells->addWidget(bout);
    }
}

void LayoutBarreOutil::phasePlacement()
{
    qDebug() << "phase placement";
    m_bar_vie->setValue(m_parent->getJeu()->getPerso()->getVie());
    m_bout_passer_tour->setEnabled(true);
    setPret(false);
}

void LayoutBarreOutil::phaseFight()
{
    m_bout_passer_tour->setText(trUtf8("Passer mon tour"));
}

void LayoutBarreOutil::setPret(bool pret)
{
    if(pret)
        m_bout_passer_tour->setText(trUtf8("Pas Prêt"));
    else
        m_bout_passer_tour->setText(trUtf8("Prêt"));
}

void LayoutBarreOutil::setMonTour(bool monTour)
{
    qDebug() << "mon tour";
    m_bout_passer_tour->setEnabled(monTour);
}

void LayoutBarreOutil::setPC(int pc)
{
    m_labelPC->setText(QString::number(pc));
}

void LayoutBarreOutil::setVie(int vie)
{
    m_bar_vie->setValue(vie);
}
