#ifndef ENTITYACTIONS_H
#define ENTITYACTIONS_H

#include "graphic/subwindow.h"
#include "graphicGame/gamefield.h"

class GameField;

class EntityActions : public SubWindow
{
public:
    EntityActions(GameField *gameField);
protected:
    virtual void closeActions();
private:
    QPushButton m_cancelButton;
    QPushButton m_exchangeButton;
    QPushButton m_privateMessageButton;
    QPushButton m_fightButton;
};

#endif // ENTITYACTIONS_H
