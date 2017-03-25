#include "additionalWindows/dialoguepnj.h"

Bouton_num::Bouton_num(QString const& texte, int num) : QPushButton(texte)
{
    m_num = num;
    connect(this, SIGNAL(clicked()), this, SLOT(cliquer()));
}

void Bouton_num::cliquer()
{
    emit clique(m_num);
}


Dialoguepnj::Dialoguepnj(QWidget *parent, NPC *pers, QString *rep) : QDialog(parent)
{
    m_lay = new QVBoxLayout;
    m_reponse = rep;
    *m_reponse = "";
    m_replique = new QPlainTextEdit;
    m_replique->setReadOnly(true);
    m_replique->setPlainText(pers->replique());
    m_repactuelles = pers->reponses();
    affiche();
    this->exec();
}

void Dialoguepnj::reponsecliquee(int num)
{
    if(!repliqueFinale(m_repactuelles->pistenum(num)->replique()))
    {
        m_replique->setPlainText(m_repactuelles->pistenum(num)->replique());
        m_repactuelles = m_repactuelles->pistenum(num)->reponses();
        affiche();
    }
    else
    {
        *m_reponse = m_repactuelles->pistenum(num)->replique().section('_',1);
        this->close();
    }
}

void Dialoguepnj::affiche()
{
    m_lay->removeWidget(m_replique);
    delete m_lay;
    m_lay = new QVBoxLayout;
    m_lay->addWidget(m_replique);
    m_reponses.clear();
    Bouton_num *but = 0;
    for(int i = 0; i < m_repactuelles->nbrpistes(); i++)
    {
        but = new Bouton_num(m_repactuelles->pistenum(i)->reponse(), i);
        connect(but, SIGNAL(clique(int)), this, SLOT(reponsecliquee(int)));
        m_reponses.push_back(but);
        m_lay->addWidget(but);
    }
    this->setLayout(m_lay);
}
