#ifndef LAYGAME_H
#define LAYGAME_H

#include <QVBoxLayout>
#include <QGraphicsView>

class LayGame : public QVBoxLayout
{
public:
    LayGame();
    QGraphicsView m_game;
    QFrame m_toolBar;
};

#endif // LAYGAME_H
