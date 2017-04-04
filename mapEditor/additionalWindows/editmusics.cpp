#include "editmusics.h"
#include "ui_editmusics.h"

EditerMusiques::EditerMusiques(QWidget *parent, QVector<QString>*musiques) :
    QDialog(parent),
    ui(new Ui::EditerMusiques)
{
    m_musiques = musiques;
    ui->setupUi(this);
    m_nbr = 0;
    connect(ui->bout_ajouter, SIGNAL(clicked()), this, SLOT(ajouter()));
    connect(this, SIGNAL(accepted()), this, SLOT(accepter()));
    for(int i = 0; i < musiques->size(); i++)
    {
        ajouter();
        ui->tableau->setItem(i, 0, new QTableWidgetItem((*musiques)[i]));
    }
    this->exec();
}

EditerMusiques::~EditerMusiques()
{
    delete ui;
}

void EditerMusiques::ajouter()
{
    ui->tableau->insertRow(m_nbr);
    m_nbr++;
}

void EditerMusiques::accepter()
{
    m_musiques->clear();
    for(int i = 0; i < m_nbr; i++)
    {
        m_musiques->push_back(ui->tableau->item(i, 0)->text());
    }
}
