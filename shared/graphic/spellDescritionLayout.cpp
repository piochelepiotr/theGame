#include "layoutdescriptionsort.h"

LayoutDescriptionSort::LayoutDescriptionSort(Personnage *personnage) :
    QHBoxLayout()
{
    m_differentsSorts = new QVBoxLayout();
    m_personnage = personnage;
    m_descriptionSort = new Description_sort();
    this->addLayout(m_differentsSorts);
    this->addWidget(m_descriptionSort);
    chargeSorts();
}

void LayoutDescriptionSort::chargeSorts()
{
    QMap<QString,Sort*> sorts = m_personnage->sorts();
    LayoutUnSort *layout = 0;
    for(QMap<QString,Sort*>::const_iterator it = sorts.begin(); it != sorts.end(); it++)
    {
        layout = new LayoutUnSort(it.value());
        connect(layout,SIGNAL(clique(QString)),this,SLOT(sortClique(QString)));
        m_differentsSorts->addWidget(layout);
    }
}

void LayoutDescriptionSort::sortClique(QString const& nom)
{
    m_descriptionSort->setSort(m_personnage->donneesEditeur()->ressources->getSort(nom));
}
