#ifndef TOOLTIP_H
#define TOOLTIP_H

#include <QGraphicsTextItem>
#include <QPainter>

class ToolTip : public QGraphicsTextItem
{
public:
    ToolTip(QString const& text);
protected:
    void paint( QPainter *painter, const QStyleOptionGraphicsItem *o, QWidget *w);
};

#endif // TOOLTIP_H
