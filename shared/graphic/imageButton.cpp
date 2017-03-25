#include "graphic/imageButton.h"

ImageButtonString::ImageButtonString(QString nom,QString const& cheminImage) : QPushButton()
{
    m_nom = nom;
    setIconSize(QSize(20,20));
    setIcon(QIcon(cheminImage));
    connect(this, SIGNAL(clicked()), this, SLOT(clique()));
}

void ImageButtonString::clique()
{
    emit clique(m_nom);
}
