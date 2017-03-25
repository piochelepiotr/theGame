#include "graphic/spellDescriptionLayout.h"

SpellDescriptionLayout::SpellDescriptionLayout(Character *personnage) :
    QHBoxLayout()
{
    m_differentsSorts = new QVBoxLayout();
    m_personnage = personnage;
    m_descriptionSort = new SpellDescription();
    this->addLayout(m_differentsSorts);
    this->addWidget(m_descriptionSort);
    chargeSorts();
}

void SpellDescriptionLayout::chargeSorts()
{
    QMap<QString,Spell*> sorts = m_personnage->sorts();
    SpellLayout *layout = 0;
    for(QMap<QString,Spell*>::const_iterator it = sorts.begin(); it != sorts.end(); it++)
    {
        layout = new SpellLayout(it.value());
        connect(layout,SIGNAL(clique(QString)),this,SLOT(sortClique(QString)));
        m_differentsSorts->addWidget(layout);
    }
}

void SpellDescriptionLayout::sortClique(QString const& nom)
{
    m_descriptionSort->setSort(m_personnage->donneesEditeur()->ressources->getSort(nom));
}
