#ifndef BASIC_GEOMETRY_H
#define BASIC_GEOMETRY_H

#include "structures_point.h"

int vect(const point <int> &p0,const point <int> &a, const point <int> &b);
int dist(const point <int> &a, const point <int> &b);
double hypotenuse(const double &side_a, const double &side_b);
point <int> intersection(const point <int> &a, const point <int> &b, const point <int> &c, const point <int> &d);

#endif
