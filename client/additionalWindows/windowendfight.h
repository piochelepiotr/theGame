#ifndef WINDOWENDFIGHT_H
#define WINDOWENDFIGHT_H

#include <QDialog>
#include "graphic/fightWinnings.h"
#include "entities/character.h"

namespace Ui {
class WindowEndFight;
}

class WindowEndFight : public QDialog
{
    Q_OBJECT

public:
    explicit WindowEndFight(QString const& texte,QWidget *parent,Personnage *perso);
    ~WindowEndFight();

private:
    Ui::WindowEndFight *ui;
};

#endif // WINDOWENDFIGHT_H
