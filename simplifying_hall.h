#ifndef SIMPLIFYING_HALL_H
#define SIMPLIFYING_HALL_H

#include <vector>
#include <cmath>
#include "structures.h"
#include "basicfun.h"

double ang(point a, point b, point c);
void simplifying_hall(std::vector <point> *hull);

#endif
