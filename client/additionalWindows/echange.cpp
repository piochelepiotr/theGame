#include "additionalWindows/echange.h"
#include "ui_echange.h"

Echange::Echange(Character *personnage, QString const& nom_autre, Reseau *reseau) :
    ui(new Ui::Echange)
{
    ui->setupUi(this);
    m_personnage = personnage;
    m_nom_autre = nom_autre;
    m_reseau = reseau;
}

Echange::~Echange()
{
    delete ui;
}
