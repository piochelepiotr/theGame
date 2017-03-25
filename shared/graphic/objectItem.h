#ifndef OBJSURSCENE_H
#define OBJSURSCENE_H

#include <QObject>
#include <QGraphicsPixmapItem>
#include "graphic/tooltip.h"

class GameScene;

class ObjectItem : public QGraphicsPixmapItem
{
public:
    ObjectItem(GameScene *parent, int mapWidth, QPoint const& pos = QPoint(-1,-1));
    void resize(int mapWidth);
    void displayToolTip();
    void hideToolTip();
    void changeToolTip(QString const& texte);
    void moveToolTip();

protected:

    virtual void mousePressEvent (QGraphicsSceneMouseEvent *);
    virtual void hoverEnterEvent(QGraphicsSceneHoverEvent *);
    virtual void hoverLeaveEvent(QGraphicsSceneHoverEvent *);
    GameScene *m_parent;
private:
    void createToolTip();
    int m_mapWidth;
    QPoint m_pos;
    ToolTip *m_toolTip;
    QColor m_color;
};

#endif // OBJSURSCENE_H
