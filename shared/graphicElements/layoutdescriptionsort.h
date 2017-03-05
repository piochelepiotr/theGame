#ifndef LAYOUTDESCRIPTIONSORT_H
#define LAYOUTDESCRIPTIONSORT_H

#include <QHBoxLayout>
#include "graphicElements/description_sort.h"
#include "infoJoueur/personnage.h"
#include "layoutunsort.h"

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
