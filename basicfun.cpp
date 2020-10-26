#include "basicfun.h"

int vect(point p0, point a, point b)
{
    return (a.i - p0.i)*(b.j - p0.j) - (a.j - p0.j)*(b.i - p0.i);
}
int dist(point a, point b)
{
    return (a.i - b.i)*(a.i - b.i) + (a.j - b.j)*(a.j - b.j);
}
point intersection(point a, point b, point c, point d)
{
    point p;
    double a1, a2, b1, b2, c1, c2, det;
    a1 = a.j - b.j;
    b1 = b.i - a.i;
    c1 = a.i * b.j - b.i * a.j;
    a2 = c.j - d.j;
    b2 = d.i - c.i;
    c2 = c.i * d.j - d.i * c.j;
    det = a1 * b2 - a2 * b1;
    p.i = (b1 * c2 - b2 * c1) / det;
    p.j = (a2 * c1 - a1 * c2) / det;
    return p;
}
