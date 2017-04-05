#ifndef LAYCREATECHARAC_H
#define LAYCREATECHARAC_H

#include <QPushButton>
#include <QHBoxLayout>
#include <QLabel>
#include <QSpacerItem>
#include <QLineEdit>

class LayCreateCharac : public QVBoxLayout
{
public:
    LayCreateCharac();

    //not beatiful !!!
    QHBoxLayout m_layoutButtons;
    QHBoxLayout m_layoutCharacters;
    QPushButton m_buttonNext;
    QPushButton m_buttonPrevious;
    QPushButton m_buttonCreate;
    QPushButton m_buttonCancel;
    QLabel m_imageCharacter;
    //QSpacerItem m_spacerLeft;
    //QSpacerItem m_spacerRight;
    QLabel m_labelName;
    QLineEdit m_nameCharacter;
};

#endif // LAYCREATECHARAC_H
