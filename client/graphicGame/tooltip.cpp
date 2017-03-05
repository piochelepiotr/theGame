#include "tooltip.h"

ToolTip::ToolTip(const QString &text) : QGraphicsTextItem(text)
{
    setZValue(100);
    setDefaultTextColor(Qt::white);
}

void ToolTip::paint( QPainter *painter, const QStyleOptionGraphicsItem *o, QWidget *w)
{
    painter->setBrush(Qt::black);
    painter->drawRect(boundingRect());
    QGraphicsTextItem::paint(painter, o, w);
}
