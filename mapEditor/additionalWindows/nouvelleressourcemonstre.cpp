#include "nouvelleressourcemonstre.h"
#include "ui_nouvelleressourcemonstre.h"

NouvelleRessourceMonstre::NouvelleRessourceMonstre(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::NouvelleRessourceMonstre)
{
    ui->setupUi(this);
}

NouvelleRessourceMonstre::~NouvelleRessourceMonstre()
{
    delete ui;
}
