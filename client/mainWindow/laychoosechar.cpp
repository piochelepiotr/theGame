#include "laychoosechar.h"

LayChooseChar::LayChooseChar()
{
    m_layoutButtons = new QHBoxLayout();
    m_layoutCharacters = new QHBoxLayout();
    m_buttonNext = new QPushButton();
    m_buttonPrevious = new QPushButton();
    m_buttonCreate = new QPushButton("Créer un personnage");
    m_buttonDelete = new QPushButton();
    m_buttonPlay = new QPushButton("Entrer dans le jeu");
    m_imageCharacter = new QLabel();
    m_nameCharacter = new QLabel();
    m_mainLayout = new QVBoxLayout();

    this->setLayout(m_mainLayout);

    m_layoutButtons->addWidget(m_buttonCreate);
    m_layoutButtons->addStretch();
    //m_layoutButtons->addSpacerItem(m_spacerLeft);
    m_layoutButtons->addWidget(m_nameCharacter);
    m_layoutButtons->addWidget(m_buttonDelete);
    m_layoutButtons->addStretch();
    //m_layoutButtons->addSpacerItem(m_spacerRight);
    m_layoutButtons->addWidget(m_buttonPlay);

    m_layoutCharacters->addWidget(m_buttonPrevious);
    m_layoutCharacters->addWidget(m_imageCharacter);
    m_layoutCharacters->addWidget(m_buttonNext);

    m_mainLayout->addLayout(m_layoutCharacters);
    m_mainLayout->addLayout(m_layoutButtons);
}
