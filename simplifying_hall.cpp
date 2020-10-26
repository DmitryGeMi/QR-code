#include <vector>
#include "structures_and_basicfun.h"
#include <cmath>

double ang(point a, point b, point c)
{
    return ((c.i - b.i)*(b.i - a.i) + (c.j - b.j)*(b.j - a.j)) / (sqrt(dist(a, b))*(sqrt(dist(c, b))));
}
void simplifying_hall(std::vector <point> *hull)
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