#ifndef ADD_H
#define ADD_H

#include <vector>

struct point
{
    int i;
    int j;
};
std::vector<point> convex_hull(std::vector<point> pnt);
int vect(point p0, point a, point b);
int dist(point a, point b);

#endif
