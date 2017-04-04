#include "editmapmonsters.h"
#include "ui_editmapmonsters.h"

EditerMonstreDeLaMap::EditerMonstreDeLaMap(QWidget *parent, QMap<QString, double> *monstres,QStringList nomMonstres) :
    QDialog(parent),
    ui(new Ui::EditerMonstreDeLaMap)
{
    m_monstres = monstres;
    m_nomMonstres = nomMonstres;
    ui->setupUi(this);
    m_nbr = 0;
    connect(ui->bout_ajouter, SIGNAL(clicked()), this, SLOT(ajouter()));
    connect(this, SIGNAL(accepted()), this, SLOT(accepter()));

    for(QMap<QString, double>::iterator it = m_monstres->begin(); it != m_monstres->end(); it++)
    {
        ajouter();
        ui->tableau->setItem(m_nbr-1, 0, new QTableWidgetItem(it.key()));
        ui->tableau->setItem(m_nbr-1, 1, new QTableWidgetItem(QString::number(it.value())));
    }

    this->exec();
}

EditerMonstreDeLaMap::~EditerMonstreDeLaMap()
{
    delete ui;
}

void EditerMonstreDeLaMap::ajouter()
{
    ui->tableau->insertRow(m_nbr);
    NumberButton *bout = new NumberButton("supprimer",m_nbr);
    QComboBox *monstres = new QComboBox();
    monstres->addItems(m_nomMonstres);
    QDoubleSpinBox *proba = new QDoubleSpinBox();

    ui->tableau->setCellWidget(m_nbr,0,monstres);
    ui->tableau->setCellWidget(m_nbr,1,proba);
    ui->tableau->setCellWidget(m_nbr,2,bout);

    connect(bout,SIGNAL(clique(int)),this,SLOT(supprimer(int)));
    m_nbr++;
}

void EditerMonstreDeLaMap::supprimer(int num)
{
    ui->tableau->removeRow(num);
    m_nbr--;
    NumberButton *bout = 0;
    for(int i = num; i < m_nbr;i++)
    {
        bout = (NumberButton*) ui->tableau->cellWidget(i,2);
        bout->moinsnum();
    }
}

void EditerMonstreDeLaMap::accepter()
{
    m_monstres->clear();
    for(int i = 0; i < m_nbr; i++)
    {
        QComboBox *monstres = (QComboBox*) ui->tableau->cellWidget(i,0);
        QDoubleSpinBox *proba = (QDoubleSpinBox*) ui->tableau->cellWidget(i,1);
        (*m_monstres)[monstres->currentText()] = proba->value();
    }
}
