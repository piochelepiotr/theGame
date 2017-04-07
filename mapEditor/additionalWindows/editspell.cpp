#include "editspell.h"
#include "ui_editspell.h"

EditerUnSpell::EditerUnSpell(QWidget *parent, SpellModel *editer, bool creation) :
    QDialog(parent),
    ui(new Ui::EditerUnSpell)
{
    m_creation = creation;
    ui->setupUi(this);
    m_editer = editer;
    charge();
    connect(this, SIGNAL(accepted()), this, SLOT(accepter()));
    exec();
}

EditerUnSpell::~EditerUnSpell()
{
    delete ui;
}

void EditerUnSpell::accepter()
{
    enregistre();
}

void EditerUnSpell::enregistre()
{
    QString texte = m_editer->name() +'/'+QString::number(ui->lvl->value());
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
    m_editer->recharge(texte);
    if(m_creation)
    {
        QFile fichier(QString(DONNEES)+QString("spells.txt"));
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
        QFile fichier(QString(DONNEES)+QString("spells.txt")), fichier2(QString(DONNEES)+QString("spells2.txt"));
        if(fichier.open(QIODevice::ReadOnly) && fichier2.open(QIODevice::WriteOnly))
        {
            QTextStream stream(&fichier), stream2(&fichier2);
            while(!stream.atEnd())
            {
                ligne = stream.readLine();
                if(ligne.section('/', 0, 0) == m_editer->name())
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
            QFile::remove(QString(DONNEES)+QString("spells.txt"));
            QFile::rename(QString(DONNEES)+QString("spells2.txt"), QString(DONNEES)+QString("spells.txt"));
        }
    }
}

void EditerUnSpell::charge()
{
    setWindowTitle(m_editer->name());
    QString texte;
    if(!m_creation)
    {
        QFile fichier(QString(DONNEES)+QString("spells.txt"));
        if(fichier.open(QIODevice::ReadOnly))
        {
            QTextStream stream(&fichier);
            while(!stream.atEnd() && texte.section('/', 0, 0) != m_editer->name())
            {
                texte = stream.readLine();
            }
            if(texte.section('/', 0, 0) != m_editer->name())
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

void EditerUnSpell::supprimer(QString const& name)
{
    QString ligne;
    QFile fichier(QString(DONNEES)+QString("spells.txt")), fichier2(QString(DONNEES)+QString("spells2.txt"));
    if(fichier.open(QIODevice::ReadOnly) && fichier2.open(QIODevice::WriteOnly))
    {
        QTextStream stream(&fichier), stream2(&fichier2);
        while(!stream.atEnd())
        {
            ligne = stream.readLine();
            if(ligne.section('/', 0, 0) != name)
            {
                stream2 << ligne << endl;
            }
        }
        fichier.close();
        fichier2.close();
        QFile::remove(QString(DONNEES)+QString("spells.txt"));
        QFile::rename(QString(DONNEES)+QString("spells2.txt"), QString(DONNEES)+QString("spells.txt"));
    }
}
