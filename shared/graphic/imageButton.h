#ifndef BOUTONIMG_H
#define BOUTONIMG_H

#include <QPushButton>

class BoutonImgString : public QPushButton
{
    Q_OBJECT

public:
    BoutonImgString(QString nom,QString const& cheminImage);

public slots:
    void clique();
signals:
    void clique(QString nom);

private:
    QString m_nom;
};

#endif // BOUTONIMG_H
