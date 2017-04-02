#ifndef WINDOWACTIONS_H
#define WINDOWACTIONS_H

#include "graphic/subwindow.h"
#include <QPushButton>
#include <QHBoxLayout>

class GameScene;

class WindowActions : public SubWindow
{
    Q_OBJECT
public:
    WindowActions(GameScene *gameScene, const QString &clas,QString const& name);

signals:
    void attackMonster(QString const& name);

public slots:
    void fight();

private:
    QString m_name;
    QPushButton m_fightButton;
    QHBoxLayout m_layout;
};

#endif // WINDOWACTIONS_H
