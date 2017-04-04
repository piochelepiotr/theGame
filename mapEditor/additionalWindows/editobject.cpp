#include "editobject.h"
#include "ui_editobject.h"

EditerUnObjet::EditerUnObjet(QWidget *parent,bool *ok,Object *objet, bool creation,int lcase, int hcase, QString *chemin, bool *supprimer) :
    QDialog(parent),
    ui(new Ui::EditerUnObjet)
{
    m_lcase = lcase;
    m_hcase = hcase;
    ui->setupUi(this);
    m_chemin = chemin;
    m_ok = ok;
    m_supprimer = supprimer;
    m_objet = objet;
    ui->nom->setText(m_objet->nom());
    ui->propx->setValue(m_objet->propx());
    ui->propy->setValue(m_objet->propy());
    if(creation)
        ui->supprimer->setEnabled(false);
    connect(this, SIGNAL(accepted()), this, SLOT(accepter()));
    connect(this, SIGNAL(rejected()), this, SLOT(refuser()));
    connect(ui->supprimer, SIGNAL(clicked()), this, SLOT(supprimer()));
    this->exec();
}

EditerUnObjet::~EditerUnObjet()
{
    delete ui;
}

void EditerUnObjet::accepter()
{
    if(m_chemin)
    {
        *m_chemin = QFileDialog::getOpenFileName(this, "Selectionnez l'image", "home/wolski/Documents/Piotr", "Images (*.png)");
    }
    (*m_ok) = true;
    valeurs();
}

void EditerUnObjet::refuser()
{
    (*m_ok) = false;
    valeurs();
}

void EditerUnObjet::valeurs()
{
    m_objet->setNom(ui->nom->text());
    m_objet->setPropx(ui->propx->value(), m_lcase, m_hcase);
    m_objet->setPropy(ui->propy->value(), m_lcase, m_hcase);
}

void EditerUnObjet::supprimer()
{
    if(m_supprimer)
        *m_supprimer = true;
    reject();
}

