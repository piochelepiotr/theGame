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

    void sortClique(QString const& nom);

private:
    void chargeSorts();

    QVBoxLayout *m_differentsSorts;
    SpellDescription *m_descriptionSort;
    Character *m_personnage;
};

#endif // LAYOUTDESCRIPTIONSORT_H
