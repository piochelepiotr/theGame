#ifndef LAYCREATECHARAC_H
#define LAYCREATECHARAC_H

#include <QPushButton>
#include <QHBoxLayout>
#include <QLabel>
#include <QSpacerItem>
#include <QLineEdit>

class LayCreateCharac : public QWidget
{
public:
    LayCreateCharac();

    //not beatiful !!!
    QHBoxLayout *m_layoutButtons;
    QHBoxLayout *m_layoutCharacters;
    QPushButton *m_buttonNext;
    QPushButton *m_buttonPrevious;
    QPushButton *m_buttonCreate;
    QPushButton *m_buttonCancel;
    QLabel *m_imageCharacter;
    QLabel *m_labelName;
    QLineEdit *m_nameCharacter;
    QVBoxLayout *m_mainLayout;
};

#endif // LAYCREATECHARAC_H
