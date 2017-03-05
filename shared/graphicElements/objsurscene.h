#ifndef OBJSURSCENE_H
#define OBJSURSCENE_H

#include <QObject>
#include <QGraphicsPixmapItem>

class GameScene;

class ObjSurScene : public QGraphicsPixmapItem
{
public:
    ObjSurScene(GameScene *parent, int largeurScene, QPoint const& pos = QPoint(-1,-1));
    void utile(QString const& aide);
    void inutile();
    void redi(int largeurScene);

protected:

    void mousePressEvent (QGraphicsSceneMouseEvent *);
private:
    bool m_utile;
    int m_largeurScene;
    QPoint m_pos;
    GameScene *m_parent;
};

#endif // OBJSURSCENE_H
