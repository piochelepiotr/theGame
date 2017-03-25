#include "graphic/numberButton.h"

NumberButton::NumberButton(const QString &texte, int num) : QPushButton(texte)
{
    m_num = num;
    connect(this, SIGNAL(clicked()), this, SLOT(clique()));
}

void NumberButton::clique()
{
    emit clique(m_num);
}
