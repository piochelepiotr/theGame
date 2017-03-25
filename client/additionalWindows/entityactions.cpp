#include "entityactions.h"

EntityActions::EntityActions(GameField *gameField) : SubWindow(gameField,Centered,700,400)
  ,m_cancelButton("Annuler")
  ,m_fightButton("Combattre")
  ,m_privateMessageButton("Envoyer un message privé")
  ,m_exchangeButton("Lancer un échange")
{ 
    QHBoxLayout *layout = new QHBoxLayout();
    layout->addWidget(&m_cancelButton);
    layout->addWidget(&m_fightButton);
    layout->addWidget(&m_privateMessageButton);
    layout->addWidget(&m_exchangeButton);
    m_content.setLayout(layout);
}

void EntityActions::closeActions()
{

}
