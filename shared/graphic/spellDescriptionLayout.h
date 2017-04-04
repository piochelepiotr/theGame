#ifndef LAYOUTDESCRIPTIONSORT_H
#define LAYOUTDESCRIPTIONSORT_H

#include <QHBoxLayout>
#include "graphic/spellDescription.h"
#include "entities/character.h"
#include "spellLayout.h"

class SpellDescriptionLayout : public QHBoxLayout
{
    Q_OBJECT
public:
    explicit SpellDescriptionLayout(Character *personnage);

signals:

public slots:

    void spellClique(QString const& nom);

private:
    void chargeSpells();

    QVBoxLayout *m_differentsSpells;
    SpellDescription *m_descriptionSpell;
    Character *m_personnage;
};

#endif // LAYOUTDESCRIPTIONSORT_H
