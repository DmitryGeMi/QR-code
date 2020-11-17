#include <vector>
#include <stdexcept>
#include "structures_point.h"
#include "basic_geometry.h"

std::vector<point <int>> convex_hull(const std::vector<point <int>> &point_vect) {
    if (point_vect.size() == 0)
        throw std::runtime_error("Input image does not contain a black barcode");
    std::vector<point <int>> secondary_point_vect = point_vect;
    point <int> p0 = secondary_point_vect[0];
    point <int> p1;
    int i = 0, k = 0, m = 1;
    for (point <int> p : secondary_point_vect)
    {
        if ((p.i > p0.i) || (p.j == p0.j && p.j < p0.j))
        {
            p0 = p;
            k = i;
        }
        i++;
    }
    p1 = secondary_point_vect[0];
    secondary_point_vect[0] = p0;
    secondary_point_vect[k] = p1;
    p1 = p0;
    bool flg = false;
    std::vector<point <int>> hull = { p0 };
    while (flg == false)
    {
        for (i = 1; i < secondary_point_vect.size(); i++)
        {
            if ((vect(p1, secondary_point_vect[m], secondary_point_vect[i]) < 0) || (vect(p1, secondary_point_vect[m], secondary_point_vect[i]) == 0) && (dist(p1, secondary_point_vect[m]) < dist(p1, secondary_point_vect[i])))
            {
                m = i;
            }
        }
        if ((secondary_point_vect[m].i == p0.i) && (secondary_point_vect[m].j == p0.j))
            flg = true;
        else {
            p1 = secondary_point_vect[m];
            m = 0;
            hull.push_back(p1);
        }
    }
    return hull;
}
