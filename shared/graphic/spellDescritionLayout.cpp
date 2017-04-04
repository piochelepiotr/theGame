#include "graphic/spellDescriptionLayout.h"

SpellDescriptionLayout::SpellDescriptionLayout(Character *personnage) :
    QHBoxLayout()
{
    m_differentsSpells = new QVBoxLayout();
    m_personnage = personnage;
    m_descriptionSpell = new SpellDescription();
    this->addLayout(m_differentsSpells);
    this->addWidget(m_descriptionSpell);
    chargeSpells();
}

void SpellDescriptionLayout::chargeSpells()
{
    QMap<QString,Spell*> spells = m_personnage->spells();
    SpellLayout *layout = 0;
    for(QMap<QString,Spell*>::const_iterator it = spells.begin(); it != spells.end(); it++)
    {
        layout = new SpellLayout(it.value());
        connect(layout,SIGNAL(clique(QString)),this,SLOT(spellClique(QString)));
        m_differentsSpells->addWidget(layout);
    }
}

void SpellDescriptionLayout::spellClique(QString const& name)
{
    m_descriptionSpell->setSpell(m_personnage->donneesEditeur()->resources->getSpell(name));
}
