#include "entities/characterModel.h"


Classe::Classe(QString const& donnees, const QMap<QString, UnSort *> &sorts)
{
    QStringList liste = donnees.split('/');
    m_classe = liste[0];
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
            m_sorts[liste.front()] = sorts[liste.front()];
        liste.pop_front();
    }
}
