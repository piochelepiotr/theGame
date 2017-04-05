#ifndef LAYGAME_H
#define LAYGAME_H

#include <QVBoxLayout>
#include <QGraphicsView>

class LayGame : public QWidget
{
    Q_OBJECT
public:
    LayGame();
    QGraphicsView *m_game;
    QFrame *m_toolBar;
    QVBoxLayout *m_mainLayout;
};

#endif // LAYGAME_H
