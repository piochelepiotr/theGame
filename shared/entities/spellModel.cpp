#include "entities/spellModel.h"

UnSort::UnSort(const QString &donnees)
{
    QStringList liste = donnees.split('/');
    m_nom = liste[0];
    liste.pop_front();
    m_niveau = liste[0].toInt();
    liste.pop_front();
    for(int i = 0; i < NBR_LVL_SORTS; i++)
    {
        m_niveaux.push_back(new Sort(m_nom,i, liste[i*5+0].toInt(), liste[i*5+1].toInt(), liste[i*5+2].toInt(), liste[i*5+3].toInt(), liste[i*5+4].toInt()));
    }
}

void UnSort::recharge(QString const& donnees)
{
    QStringList liste = donnees.split('/');
    liste.pop_front();
    m_niveau = liste[0].toInt();
    for(int i = 0; i < NBR_LVL_SORTS; i++)
    {
        delete m_niveaux[i];
        m_niveaux[i] = new Sort(m_nom,i, liste[i*5+0].toInt(), liste[i*5+1].toInt(), liste[i*5+2].toInt(), liste[i*5+3].toInt(), liste[i*5+4].toInt());
    }
}

UnSort *UnSort::nouveau(QString const& nom)
{
    QString donnees = nom + "/0";
    for(int i = 0; i < NBR_LVL_SORTS; i++)
    {
        donnees += "/0/0/0/0/0";
    }
    return new UnSort(donnees);
}

UnSort::~UnSort()
{
    for(int i = 0; i < NBR_LVL_SORTS; i++)
    {
        delete m_niveaux[i];
    }
}
