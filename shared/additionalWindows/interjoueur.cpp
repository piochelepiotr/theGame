#include "additionalWindows/interjoueur.h"
#include "ui_interjoueur.h"

InterJoueur::InterJoueur(QWidget *parent, QString const& nom, Inter *inter) :
    QDialog(parent),
    ui(new Ui::InterJoueur)
{
    m_inter = inter;
    *m_inter = Annuler;
    ui->setupUi(this);
    connect(ui->bout_annul, SIGNAL(clicked()), this, SLOT(reject()));
    connect(ui->bout_ech, SIGNAL(clicked()), this, SLOT(echange()));
    connect(ui->bout_def, SIGNAL(clicked()), this, SLOT(defi()));
    this->exec();
}

InterJoueur::~InterJoueur()
{
    delete ui;
}

void InterJoueur::echange()
{
    *m_inter = Echange;
    close();
}

void InterJoueur::defi()
{
    *m_inter = Defi;
    close();
}

