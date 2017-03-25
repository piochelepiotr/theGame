#ifndef GAINUNPERSOCOMBAT_H
#define GAINUNPERSOCOMBAT_H

#include <QHBoxLayout>
#include <QLabel>
#include "entities/character.h"

class FightWinnings : public QHBoxLayout
{
    Q_OBJECT
public:
    explicit FightWinnings(QString const& text,Character *perso);

signals:

public slots:

};

#endif // GAINUNPERSOCOMBAT_H
