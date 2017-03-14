#include "bouton.h"

Bouton::Bouton(const QString &texte, int num) : QPushButton(texte)
{
    m_num = num;
    connect(this, SIGNAL(clicked()), this, SLOT(clique()));
}

void Bouton::clique()
{
    emit clique(m_num);
}
