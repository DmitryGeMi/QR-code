#include <vector>

struct point
{
    int i;
    int j;
};
int vect(point p0, point a, point b)
{
    return (a.i - p0.i)*(b.j - p0.j) - (a.j - p0.j)*(b.i - p0.i);
}
int dist(point a, point b)
{
    return (a.i - b.i)*(a.i - b.i) + (a.j - b.j)*(a.j - b.j);
}
std::vector<point> convex_hull(std::vector<point> pnt) {
    point p0 = pnt[0];
    point p1;
    int i = 0, k = 0, m = 1;
    for (point p : pnt)
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
    std::vector<point> hull = { p0 };
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
