#include "entities/characterModel.h"


CharacterModel::CharacterModel(QString const& donnees, const QMap<QString, SpellModel *> &spells)
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
        if(spells.contains(liste.front()))
            m_spells[liste.front()] = spells[liste.front()];
        liste.pop_front();
    }
}
