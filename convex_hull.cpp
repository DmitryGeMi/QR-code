#include <vector>
#include "structures_point.h"
#include "basicfun.h"

std::vector<point <int>> convex_hull(std::vector<point <int>> pnt) {
    point <int> p0 = pnt[0];
    point <int> p1;
    int i = 0, k = 0, m = 1;
    for (point <int> p : pnt)
    {
        if ((p.i > p0.i) || (p.j == p0.j && p.j < p0.j))
        {
            p0 = p;
            k = i;
        }
        i++;
    }
    p1 = pnt[0];
    pnt[0] = p0;
    pnt[k] = p1;
    p1 = p0;
    bool flg = false;
    std::vector<point <int>> hull = { p0 };
    while (flg == false)
    {
        for (i = 1; i < pnt.size(); i++)
        {
            if ((vect(p1, pnt[m], pnt[i]) < 0) || (vect(p1, pnt[m], pnt[i]) == 0) && (dist(p1, pnt[m]) < dist(p1, pnt[i])))
            {
                m = i;
            }
        }
        if ((pnt[m].i == p0.i) && (pnt[m].j == p0.j))
            flg = true;
        else {
            p1 = pnt[m];
            m = 0;
            hull.push_back(p1);
        }
    }
    return hull;
}
