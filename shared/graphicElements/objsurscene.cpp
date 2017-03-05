#include "objsurscene.h"
#include "gamescene.h"

ObjSurScene::ObjSurScene(GameScene *parent, int largeurScene, QPoint const& pos) : QGraphicsPixmapItem()
{
    m_parent = parent;
    m_pos = pos;
    m_utile = false;
    parent->addItem(this);
    m_largeurScene = largeurScene;
    setAcceptedMouseButtons(Qt::RightButton);
}

void ObjSurScene::utile(QString const& aide)
{
    setToolTip(aide);
    m_utile = true;
    setAcceptHoverEvents(true);
}

void ObjSurScene::redi(int largeurScene)
{
    m_largeurScene = largeurScene;
}

void ObjSurScene::inutile()
{
    setToolTip("");
    setAcceptHoverEvents(false);
    m_utile = false;
}

void ObjSurScene::mousePressEvent ( QGraphicsSceneMouseEvent *)
{
    if(m_utile)
    {
        qDebug() << "Clique utile dans objsurscene : " << toolTip();
        m_parent->utileClique(m_pos);
    }
}
