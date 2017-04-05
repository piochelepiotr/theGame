#include "graphic/objectItem.h"
#include "gamescene.h"
#include <QGraphicsColorizeEffect>


ObjectItem::ObjectItem(GameScene *parent, int mapWidth, QPoint const& pos) : QGraphicsPixmapItem()
{
    m_color = QColor(255,255,255,50);
    m_parent = parent;
    m_pos = pos;
    parent->addItem(this);
    m_mapWidth = mapWidth;
    setAcceptedMouseButtons(Qt::RightButton);
    createToolTip();
}

void ObjectItem::resize(int mapWidth)
{
    m_mapWidth = mapWidth;
}

void ObjectItem::createToolTip()
{
    m_toolTip = new ToolTip();
    m_parent->addItem(m_toolTip);
    m_toolTip->setVisible(false);
}

void ObjectItem::moveToolTip()
{
    int posx = this->x();
    int posy = this->y() - (m_toolTip->boundingRect().height()+3);
    if(posy < 0)
    {
        posy = this->y() + pixmap().height() + 3;
    }
    posx = this->x()+pixmap().width()/2 - m_toolTip->boundingRect().width()/2;
    m_toolTip->setPos(posx,posy);
}

void ObjectItem::displayToolTip()
{
    QGraphicsColorizeEffect* colEffect = new QGraphicsColorizeEffect();
    colEffect->setColor(m_color);
    setGraphicsEffect(colEffect);
    moveToolTip();
    m_toolTip->setVisible(true);
}

void ObjectItem::hideToolTip()
{
    setGraphicsEffect(0);
    m_toolTip->setVisible(false);
}

void ObjectItem::changeToolTip(QString const& texte)
{
    m_toolTip->setPlainText(texte);
    if(m_toolTip->isEmpty())
    {
        setAcceptHoverEvents(false);
    }
    else
    {
        setAcceptHoverEvents(true);
    }
}

void ObjectItem::hoverEnterEvent(QGraphicsSceneHoverEvent *)
{
    displayToolTip();
}

void ObjectItem::hoverLeaveEvent(QGraphicsSceneHoverEvent *)
{
    hideToolTip();
}

void ObjectItem::mousePressEvent ( QGraphicsSceneMouseEvent *)
{
    if(m_toolTip->isEmpty())
    {
        qDebug() << "Clique utile dans objsurscene : " << toolTip();
        m_parent->utileClique(m_pos);
    }
}
