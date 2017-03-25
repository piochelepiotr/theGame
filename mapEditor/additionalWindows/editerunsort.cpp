#include "editerunsort.h"
#include "ui_editerunsort.h"

EditerUnSort::EditerUnSort(QWidget *parent, SpellModel *sort, bool creation) :
    QDialog(parent),
    ui(new Ui::EditerUnSort)
{
    m_creation = creation;
    ui->setupUi(this);
    m_sort = sort;
    charge();
    connect(this, SIGNAL(accepted()), this, SLOT(accepter()));
    exec();
}

EditerUnSort::~EditerUnSort()
{
    delete ui;
}

void EditerUnSort::accepter()
{
    enregistre();
}

void EditerUnSort::enregistre()
{
    QString texte = m_sort->nom() +'/'+QString::number(ui->lvl->value());
    for(int i = 0; i < ui->tableau->rowCount(); i++)
    {
        for(int j = 0; j < ui->tableau->columnCount(); j++)
        {
            if(ui->tableau->item(i,j))
            {
                texte += '/'+ui->tableau->item(i,j)->text();
            }
        }
    }
    m_sort->recharge(texte);
    if(m_creation)
    {
        QFile fichier(QString(DONNEES)+QString("sorts.txt"));
        if(fichier.open(QIODevice::WriteOnly | QIODevice::Append))
        {
            QTextStream stream(&fichier);
            stream << texte << endl;
            fichier.close();
        }
    }
    else
    {
        QString ligne;
        QFile fichier(QString(DONNEES)+QString("sorts.txt")), fichier2(QString(DONNEES)+QString("sorts2.txt"));
        if(fichier.open(QIODevice::ReadOnly) && fichier2.open(QIODevice::WriteOnly))
        {
            QTextStream stream(&fichier), stream2(&fichier2);
            while(!stream.atEnd())
            {
                ligne = stream.readLine();
                if(ligne.section('/', 0, 0) == m_sort->nom())
                {
                    stream2 << texte << endl;
                }
                else
                {
                    stream2 << ligne << endl;
                }
            }
            fichier.close();
            fichier2.close();
            QFile::remove(QString(DONNEES)+QString("sorts.txt"));
            QFile::rename(QString(DONNEES)+QString("sorts2.txt"), QString(DONNEES)+QString("sorts.txt"));
        }
    }
}

void EditerUnSort::charge()
{
    setWindowTitle(m_sort->nom());
    QString texte;
    if(!m_creation)
    {
        QFile fichier(QString(DONNEES)+QString("sorts.txt"));
        if(fichier.open(QIODevice::ReadOnly))
        {
            QTextStream stream(&fichier);
            while(!stream.atEnd() && texte.section('/', 0, 0) != m_sort->nom())
            {
                texte = stream.readLine();
            }
            if(texte.section('/', 0, 0) != m_sort->nom())
                m_creation = true;
            fichier.close();
        }
    }
    if(!m_creation)
    {
        QStringList liste = texte.split('/');
        liste.pop_front();
        ui->lvl->setValue(liste[0].toInt());
        liste.pop_front();
        for(int i = 0; i < ui->tableau->rowCount(); i++)
        {
            for(int j = 0; j < ui->tableau->columnCount(); j++)
            {
                ui->tableau->setItem(i, j, new QTableWidgetItem(liste[0]));
                liste.pop_front();
            }
        }
    }
    else
    {
        for(int i = 0; i < ui->tableau->rowCount(); i++)
        {
            for(int j = 0; j < ui->tableau->columnCount(); j++)
            {
                ui->tableau->setItem(i, j, new QTableWidgetItem("0"));
            }
        }
    }
}

void EditerUnSort::supprimer(QString const& nom)
{
    QString ligne;
    QFile fichier(QString(DONNEES)+QString("sorts.txt")), fichier2(QString(DONNEES)+QString("sorts2.txt"));
    if(fichier.open(QIODevice::ReadOnly) && fichier2.open(QIODevice::WriteOnly))
    {
        QTextStream stream(&fichier), stream2(&fichier2);
        while(!stream.atEnd())
        {
            ligne = stream.readLine();
            if(ligne.section('/', 0, 0) != nom)
            {
                stream2 << ligne << endl;
            }
        }
        fichier.close();
        fichier2.close();
        QFile::remove(QString(DONNEES)+QString("sorts.txt"));
        QFile::rename(QString(DONNEES)+QString("sorts2.txt"), QString(DONNEES)+QString("sorts.txt"));
    }
}
