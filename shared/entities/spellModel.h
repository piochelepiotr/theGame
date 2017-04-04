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
    QString nom() const { return m_nom; }
    static SpellModel *nouveau(QString const& nom);
    ~SpellModel();
    void recharge(QString const& donnees);
private:
    QVector<Spell*>m_niveaux;
    QString m_nom;
    int m_niveau;
};

#endif // UNSORT_H
