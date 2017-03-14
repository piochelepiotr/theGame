#include "point.h"

Point::Point(int x2, int y2, int z2)
{
    x = x2;
    y = y2;
    z = z2;
}

bool operator<(Point const &a, Point const& b)
{
    if(a.z < b.z)
        return true;
    else if(a.z > b.z)
        return false;
    if(a.y < b.y)
        return true;
    else if(a.y > b.y)
        return false;
    return a.x < b.x;
}
