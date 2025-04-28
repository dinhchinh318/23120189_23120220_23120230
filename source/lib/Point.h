#ifndef _POINT_H_
#define _POINT_H_

#include "app.h"

class Point
{
public:
    int x, y;
    Point();
    bool operator==(Point other);
    void set(int x0, int y0);
    Point(int x0, int y0);
};

#endif