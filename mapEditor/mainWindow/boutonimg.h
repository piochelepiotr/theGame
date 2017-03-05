#ifndef BOUTONIMG_H
#define BOUTONIMG_H

#include <QPushButton>
#include "elementsMonde/decors.h"

class BoutonImg : public QPushButton
{
    Q_OBJECT

public:
    BoutonImg(Objet *objet);

public slots:
    void clique();
signals:
    void clique(qint16 num);

private:
    qint16 m_num;
};

#endif // BOUTONIMG_H
