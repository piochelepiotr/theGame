#include "createmonsterresource.h"
#include "ui_createmonsterresource.h"

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
