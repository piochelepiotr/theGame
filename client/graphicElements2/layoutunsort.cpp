#include "layoutunsort.h"

LayoutUnSort::LayoutUnSort(Sort *sort) : QWidget()
{
    m_nom = sort->nom();
    QHBoxLayout *layout = new QHBoxLayout();
    QLabel *labelImage = new QLabel();
    QPixmap image = QPixmap(DOSSIER_IMAGES_SORTS+sort->nom()).scaled(QSize(30,30));
    QLabel *nom = new QLabel(sort->nom());
    QLabel *niveau = new QLabel("niveau : "+QString::number(sort->niveau()));
    labelImage->setPixmap(image);
    layout->addWidget(labelImage);
    layout->addWidget(nom);
    layout->addWidget(niveau);
    this->setLayout(layout);
    installEventFilter(this);
}

bool LayoutUnSort::eventFilter(QObject *obj, QEvent *ev)
{
    if(obj == this && ev->type() == QEvent::MouseButtonPress)
    {
        emit clique(m_nom);
        return true;
    }
    else
    {
        return QWidget::eventFilter(obj,ev);
    }
}
