#include "laychoosechar.h"

LayChooseChar::LayChooseChar()
{
    m_buttonCreate.setText("Créer un personnage");
    m_buttonPlay.setText("Entrer dans le jeu");

    m_layoutButtons.addWidget(&m_buttonCreate);
    m_layoutButtons.addStretch();
    //m_layoutButtons.addSpacerItem(&m_spacerLeft);
    m_layoutButtons.addWidget(&m_nameCharacter);
    m_layoutButtons.addWidget(&m_buttonDelete);
    m_layoutButtons.addStretch();
    //m_layoutButtons.addSpacerItem(&m_spacerRight);
    m_layoutButtons.addWidget(&m_buttonPlay);

    m_layoutCharacters.addWidget(&m_buttonPrevious);
    m_layoutCharacters.addWidget(&m_imageCharacter);
    m_layoutCharacters.addWidget(&m_buttonNext);

    this->addLayout(&m_layoutCharacters);
    this->addLayout(&m_layoutButtons);
}
