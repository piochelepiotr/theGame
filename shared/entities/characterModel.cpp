#include "entities/characterModel.h"


CharacterModel::CharacterModel(QString const& donnees, const QMap<QString, SpellModel *> &sorts)
{
    QStringList liste = donnees.split('/');
    m_class = liste[0];
    liste.pop_front();
    m_arme = liste.front();
    liste.pop_front();
    m_metier = liste.front();
    liste.pop_front();
    m_propX = liste.front().toDouble();
    liste.pop_front();
    m_propY = liste.front().toDouble();
    liste.pop_front();
    while(liste.size() > 0)
    {
        if(sorts.contains(liste.front()))
            m_spells[liste.front()] = sorts[liste.front()];
        liste.pop_front();
    }
}
