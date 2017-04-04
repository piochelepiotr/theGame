#include "editgate.h"
#include "ui_editgate.h"



EditerTransporteur::EditerTransporteur(QWidget *parent, Gate *transpo,bool *ok, bool *supprimer) :
    QDialog(parent),
    ui(new Ui::EditerTransporteur)
{
    ui->setupUi(this);
    m_ok = ok;
    m_transpo = transpo;
    m_supr = supprimer;
    *m_supr = false;

    ui->nbr_cooX->setValue(transpo->getMapX());
    ui->nbr_cooY->setValue(transpo->getMapY());
    ui->nbr_cooZ->setValue(transpo->getMapZ());
    ui->bar_nom->setText(transpo->getNom());
    ui->bar_arr->setText(transpo->getNomArr());
    ui->comb_largage->setCurrentIndex((int)transpo->getLargage());

    connect(this, SIGNAL(accepted()), this, SLOT(accepter()));
    connect(this, SIGNAL(rejected()), this, SLOT(refuser()));
    connect(ui->bout_suprr, SIGNAL(clicked()), this, SLOT(supprimer()));

    this->exec();
}

EditerTransporteur::~EditerTransporteur()
{
    delete ui;
}
void EditerTransporteur::accepter()
{
    *m_ok = true;
    valeurs();
}

void EditerTransporteur::refuser()
{
    *m_ok = false;
}

void EditerTransporteur::supprimer()
{
    *m_supr = true;
    close();
}

void EditerTransporteur::valeurs()
{
    m_transpo->setMapX(ui->nbr_cooX->value());
    m_transpo->setMapY(ui->nbr_cooY->value());
    m_transpo->setMapZ(ui->nbr_cooZ->value());
    m_transpo->setNom(ui->bar_nom->text());
    m_transpo->setNomArr(ui->bar_arr->text());
    m_transpo->setLargage((Dir)ui->comb_largage->currentIndex());
}
