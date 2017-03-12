#ifndef POINT_H
#define POINT_H

class Point
{
public:
    Point(int x2 = 0, int y2 = 0, int z2 = 0);
    int x;
    int y;
    int z;
};

bool operator<(Point const &a, Point const& b);

#endif // POINT_H
