#ifndef SIMPLIFY_HALL_H
#define SIMPLIFY_HALL_H

#include <vector>
#include "structures_point.h"

double ang(point <int> a, point <int> b, point <int> c);
void simplify_hull(std::vector <point <int>> &hull, const double &parameter_delete_pnt);

#endif
