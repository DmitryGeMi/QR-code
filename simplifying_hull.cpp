#include <vector>
#include <cmath>
#include "structures_point.h"
#include "basicfun.h"

double ang(point a, point b, point c)
{
    return ((c.i - b.i)*(b.i - a.i) + (c.j - b.j)*(b.j - a.j)) / (sqrt(dist(a, b))*(sqrt(dist(c, b))));
}
void simplifying_hull(std::vector <point> *hull)
{
    int m, j;
    double e = 0.995;
    for (m = 0; m < hull->size(); m++)
    {
        if (ang(hull->at(m % hull->size()), hull->at((m + 1) % hull->size()), hull->at((m + 2) % hull->size())) > e)
        {
            j = (m + 1) % hull->size();
            hull->erase(hull->begin() + j);
        }
    }
}
