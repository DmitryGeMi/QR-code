#include <vector>
#include <cmath>
#include "structures_point.h"
#include "basic_geometry.h"

double ang(point <int> a, point <int> b, point <int> c)
{
    return ((c.i - b.i)*(b.i - a.i) + (c.j - b.j)*(b.j - a.j)) / (sqrt(dist(a, b))*(sqrt(dist(c, b))));
}
void simplify_hull(std::vector <point <int>> &hull, const double &parameter_delete_pnt)
{
    int m, j;
    for (m = 0; m < hull.size(); m++)
    {
        if (ang(hull.at(m % hull.size()), hull.at((m + 1) % hull.size()), hull.at((m + 2) % hull.size())) > parameter_delete_pnt)
        {
            j = (m + 1) % hull.size();
            hull.erase(hull.begin() + j);
        }
    }
}
