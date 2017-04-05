#include "laycreatecharac.h"

LayCreateCharac::LayCreateCharac()
{
    m_layoutButtons = new QHBoxLayout();
    m_layoutCharacters = new QHBoxLayout();
    m_buttonNext = new QPushButton();
    m_buttonPrevious = new QPushButton();
    m_buttonCreate = new QPushButton("Créer ce personnage");
    m_buttonCancel = new QPushButton("Annuler");
    m_imageCharacter = new QLabel();
    m_labelName = new QLabel();
    m_nameCharacter = new QLineEdit();
    m_mainLayout = new QVBoxLayout();

    this->setLayout(m_mainLayout);

    m_layoutButtons->addWidget(m_buttonCancel);
    m_layoutButtons->addStretch();
    m_layoutButtons->addWidget(m_labelName);
    m_layoutButtons->addWidget(m_nameCharacter);
    m_layoutButtons->addStretch();
    m_layoutButtons->addWidget(m_buttonCreate);

    m_layoutCharacters->addWidget(m_buttonPrevious);
    m_layoutCharacters->addWidget(m_imageCharacter);
    m_layoutCharacters->addWidget(m_buttonNext);

    m_mainLayout->addLayout(m_layoutCharacters);
    m_mainLayout->addLayout(m_layoutButtons);
}
