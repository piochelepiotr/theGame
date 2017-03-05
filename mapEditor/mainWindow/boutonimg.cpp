#include "boutonimg.h"

BoutonImg::BoutonImg(Objet *objet) : QPushButton()
{
    m_num = objet->numero();
    setIconSize(QSize(120,120));
    setIcon(QIcon(objet->image()));
    if(!objet->nom().isEmpty())
        setToolTip(objet->nom());
    connect(this, SIGNAL(clicked()), this, SLOT(clique()));
}

void BoutonImg::clique()
{
    emit clique(m_num);
}
