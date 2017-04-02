#ifndef WINDOWACTIONS_H
#define WINDOWACTIONS_H

#include "graphic/subwindow.h"
#include <QPushButton>
#include <QHBoxLayout>

class GameScene;

class WindowActions : SubWindow
{
    Q_OBJECT
public:
    enum Action {None,Fight};
    WindowActions(GameScene *gameScene, const QString &name, Action *action);

public slots:
    void fight();

private:
    Action *m_action;
    QPushButton m_fightButton;
    QHBoxLayout m_layout;
};

#endif // WINDOWACTIONS_H
