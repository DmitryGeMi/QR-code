#ifndef CONVEX_HULL_H
#define CONVEX_HULL_H

#include <vector>
#include "structures.h"
#include "basicfun.h"

std::vector<point> convex_hull(std::vector<point> pnt);
int vect(point p0, point a, point b);
int dist(point a, point b);

#endif
