#ifndef UNSORT_H
#define UNSORT_H

#include <QString>
#include <QVector>
#include "entities/spell.h"
#include "scenery/constants.h"

class SpellModel
{
public:
    SpellModel(QString const& donnees);
    Spell *spellNiveau(int niveau) const { return m_niveaux[niveau]; }
    QString name() const { return m_name; }
    static SpellModel *nouveau(QString const& name);
    ~SpellModel();
    void recharge(QString const& donnees);
private:
    QVector<Spell*>m_niveaux;
    QString m_name;
    int m_niveau;
};

#endif // UNSORT_H
