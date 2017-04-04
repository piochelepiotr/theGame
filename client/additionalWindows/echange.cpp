#include "additionalWindows/echange.h"
#include "ui_echange.h"

Echange::Echange(Character *personnage, QString const& name_autre, Reseau *reseau) :
    ui(new Ui::Echange)
{
    ui->setupUi(this);
    m_personnage = personnage;
    m_name_autre = name_autre;
    m_reseau = reseau;
}

Echange::~Echange()
{
    delete ui;
}
