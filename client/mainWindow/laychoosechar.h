#ifndef LAYCHOOSECHAR_H
#define LAYCHOOSECHAR_H

#include <QPushButton>
#include <QHBoxLayout>
#include <QLabel>
#include <QSpacerItem>

class LayChooseChar : public QWidget
{
public:
    LayChooseChar();

    //not beatiful !!!
    QHBoxLayout *m_layoutButtons;
    QHBoxLayout *m_layoutCharacters;
    QPushButton *m_buttonNext;
    QPushButton *m_buttonPrevious;
    QPushButton *m_buttonCreate;
    QPushButton *m_buttonDelete;
    QPushButton *m_buttonPlay;
    QLabel *m_imageCharacter;
    QLabel *m_nameCharacter;
    QVBoxLayout *m_mainLayout;
};

#endif // LAYCHOOSECHAR_H
