#include "entities/spellModel.h"

SpellModel::SpellModel(const QString &donnees)
{
    QStringList liste = donnees.split('/');
    m_name = liste[0];
    liste.pop_front();
    m_niveau = liste[0].toInt();
    liste.pop_front();
    for(int i = 0; i < NBR_LVL_SORTS; i++)
    {
        m_niveaux.push_back(new Spell(m_name,i, liste[i*5+0].toInt(), liste[i*5+1].toInt(), liste[i*5+2].toInt(), liste[i*5+3].toInt(), liste[i*5+4].toInt()));
    }
}

void SpellModel::recharge(QString const& donnees)
{
    QStringList liste = donnees.split('/');
    liste.pop_front();
    m_niveau = liste[0].toInt();
    for(int i = 0; i < NBR_LVL_SORTS; i++)
    {
        delete m_niveaux[i];
        m_niveaux[i] = new Spell(m_name,i, liste[i*5+0].toInt(), liste[i*5+1].toInt(), liste[i*5+2].toInt(), liste[i*5+3].toInt(), liste[i*5+4].toInt());
    }
}

SpellModel *SpellModel::nouveau(QString const& name)
{
    QString donnees = name + "/0";
    for(int i = 0; i < NBR_LVL_SORTS; i++)
    {
        donnees += "/0/0/0/0/0";
    }
    return new SpellModel(donnees);
}

SpellModel::~SpellModel()
{
    for(int i = 0; i < NBR_LVL_SORTS; i++)
    {
        delete m_niveaux[i];
    }
}
