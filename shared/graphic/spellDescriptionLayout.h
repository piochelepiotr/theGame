#ifndef LAYOUTDESCRIPTIONSORT_H
#define LAYOUTDESCRIPTIONSORT_H

#include <QHBoxLayout>
#include "graphic/spellDescription.h"
#include "entities/character.h"
#include "spellLayout.h"

class LayoutDescriptionSort : public QHBoxLayout
{
    Q_OBJECT
public:
    explicit LayoutDescriptionSort(Personnage *personnage);

signals:

public slots:

    void sortClique(QString const& nom);

private:
    void chargeSorts();

    QVBoxLayout *m_differentsSorts;
    Description_sort *m_descriptionSort;
    Personnage *m_personnage;
};

#endif // LAYOUTDESCRIPTIONSORT_H
