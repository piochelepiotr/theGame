#include "boutonimg.h"
#include <QVBoxLayout>
#include <QLabel>

#define BUTTON_WIDTH 120
#define BUTTON_HEIGHT 120

BoutonImg::BoutonImg(Object *objet)
{
    setFlat(true);
    m_num = objet->numero();
    setIconSize(QSize(120,120));
    setIcon(QIcon(objet->image()));
    if(!objet->name().isEmpty())
        setToolTip(objet->name());
    /*QVBoxLayout *layout = new QVBoxLayout();
    setLayout(layout);
    QLabel *image = new QLabel();
    QPixmap pix = objet->image();
    image->setPixmap(pix);
    image->setFixedSize(QSize(BUTTON_WIDTH,BUTTON_HEIGHT));
    setMinimumSize(QSize(BUTTON_WIDTH,BUTTON_HEIGHT));
    layout->addWidget(image);*/
    connect(this, SIGNAL(clicked()), this, SLOT(clique()));
}

void BoutonImg::clique()
{
    emit clique(m_num);
}
