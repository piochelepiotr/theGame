#ifndef GAINUNPERSOCOMBAT_H
#define GAINUNPERSOCOMBAT_H

#include <QHBoxLayout>
#include <QLabel>
#include "entities/character.h"

class GainUnPersoCombat : public QHBoxLayout
{
    Q_OBJECT
public:
    explicit GainUnPersoCombat(QString const& text,Personnage *perso);

signals:

public slots:

};

#endif // GAINUNPERSOCOMBAT_H
