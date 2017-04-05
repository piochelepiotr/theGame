#ifndef LAYCHOOSECHAR_H
#define LAYCHOOSECHAR_H

#include <QPushButton>
#include <QHBoxLayout>
#include <QLabel>
#include <QSpacerItem>

class LayChooseChar : public QVBoxLayout
{
public:
    LayChooseChar();

    //not beatiful !!!
    QHBoxLayout m_layoutButtons;
    QHBoxLayout m_layoutCharacters;
    QPushButton m_buttonNext;
    QPushButton m_buttonPrevious;
    QPushButton m_buttonCreate;
    QPushButton m_buttonDelete;
    QPushButton m_buttonPlay;
    QLabel m_imageCharacter;
    //QSpacerItem m_spacerLeft;
    //QSpacerItem m_spacerRight;
    QLabel m_nameCharacter;
};

#endif // LAYCHOOSECHAR_H
