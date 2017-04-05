#include "laycreatecharac.h"

LayCreateCharac::LayCreateCharac()
{
    m_buttonCreate.setText("Créer ce personnage");
    m_buttonCancel.setText("Annuler");

    m_layoutButtons.addWidget(&m_buttonCancel);
    m_layoutButtons.addStretch();
    //m_layoutButtons.addWidget(&m_spacerLeft);
    m_layoutButtons.addWidget(&m_labelName);
    m_layoutButtons.addWidget(&m_nameCharacter);
    m_layoutButtons.addStretch();
    //m_layoutButtons.addWidget(&m_spacerRight);
    m_layoutButtons.addWidget(&m_buttonCreate);

    m_layoutCharacters.addWidget(&m_buttonPrevious);
    m_layoutCharacters.addWidget(&m_imageCharacter);
    m_layoutCharacters.addWidget(&m_buttonNext);

    this->addLayout(&m_layoutCharacters);
    this->addLayout(&m_layoutButtons);
}
