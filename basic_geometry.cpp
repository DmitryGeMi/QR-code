#include <cmath>
#include "structures_point.h"

int vect(const point <int> &p0, const point <int> &a, const point <int> &b)
{
    return (a.i - p0.i)*(b.j - p0.j) - (a.j - p0.j)*(b.i - p0.i);
}
int dist(const point <int> &a, const point <int> &b)
{
    return (a.i - b.i)*(a.i - b.i) + (a.j - b.j)*(a.j - b.j);
}
double hypotenuse(const double &side_a, const double &side_b)
{
    return sqrt(side_a * side_a + side_b * side_b);
}
point <int> intersection(const point <int> &a, const point <int> &b, const point <int> &c, const point <int> &d)
{
    point <int> p;
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
