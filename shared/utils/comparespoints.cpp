#include "comparespoints.h"
#include <QPoint>

bool operator<(QPoint const &a, QPoint const& b)
{
    if(a.y() < b.y())
        return true;
    else if(a.y() > b.y())
        return false;
    if(a.x() < b.x())
        return true;
    else
        return false;
}
