#ifndef STRUCTURES_AND_BASICFUN_H
#define STRUCTURES_AND_BASICFUN_H

struct point
{
    int i;
    int j;
};
struct grad
{
    double i;
    double j;
};

int vect(point p0, point a, point b);
int dist(point a, point b);
point intersection(point a, point b, point c, point d);

#endif
