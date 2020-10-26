#include <opencv2/core/core.hpp>
#include <opencv2/imgproc.hpp>
#include <vector>
#include "structures_point.h"
#include "basicfun.h"

void add_point_pntinside(point <int> *pntinside, point <int> point1, point <int> point2)
{
    pntinside[6].i = point1.i;
    pntinside[6].j = point1.j;
    pntinside[7].i = point2.i;
    pntinside[7].j = point2.j;
}
void move_point_3_4(point <int> *pntinside)
{
    pntinside[0].i = pntinside[2].i;
    pntinside[0].j = pntinside[2].j;
    pntinside[1].i = pntinside[3].i;
    pntinside[1].j = pntinside[3].j;
}
void move_point_5_6(point <int> *pntinside)
{
    pntinside[2].i = pntinside[4].i;
    pntinside[2].j = pntinside[4].j;
    pntinside[3].i = pntinside[5].i;
    pntinside[3].j = pntinside[5].j;
}
void move_point_7_8(point <int> *pntinside)
{
    pntinside[4].i = pntinside[6].i;
    pntinside[4].j = pntinside[6].j;
    pntinside[5].i = pntinside[7].i;
    pntinside[5].j = pntinside[7].j;
}
void paint_angles(cv::Mat *img, point <int> *pntinside)
{
    point <int> t;
    for (int m = 0; m < 8; m = m + 2)
    {
        t = intersection(pntinside[m % 8], pntinside[(m + 1) % 8], pntinside[(m + 2) % 8], pntinside[(m + 3) % 8]);
        circle(*img, cv::Point(t.j, t.i), 1, cv::Scalar(50, 100, 200));
    }
}
void finding_corner_points(std::vector <point <int>> *hull, point <int> *pntinside)
{
    int k = 0, l1, l2, l3, l4, m;
    l1 = dist(hull->at(0), hull->at(1));
    l2 = dist(hull->at(1), hull->at(2));
    l3 = dist(hull->at(2), hull->at(3));
    if (hull->size() == 4)
        l4 = dist(hull->at(3), hull->at(0));
    else
        l4 = dist(hull->at(3), hull->at(4));
    for (m = 0; m < 8; m = m + 2)
    {
        pntinside[m].i = hull->at(k % hull->size()).i;
        pntinside[m].j = hull->at(k % hull->size()).j;
        pntinside[m + 1].i = hull->at((k + 1) % hull->size()).i;
        pntinside[m + 1].j = hull->at((k + 1) % hull->size()).j;
        k++;
    }
    bool flg = true;
    for (m = 4; m < hull->size(); m++)
    {
        if ((dist(hull->at(m), hull->at((m + 1) % hull->size())) >= l1) || (dist(hull->at(m), hull->at((m + 1) % hull->size())) >= l2) || (dist(hull->at(m), hull->at((m + 1) % hull->size())) >= l3) || (dist(hull->at(m), hull->at((m + 1) % hull->size())) >= l4))
        {
            flg = false;
            if ((l1 >= l4) && (l2 >= l4) && (l3 >= l4) && (flg == false))
            {
                l4 = dist(hull->at(m), hull->at((m + 1) % hull->size()));
                add_point_pntinside(pntinside, hull->at(m), hull->at((m + 1) % hull->size()));
                flg = true;
            }
            if ((l1 >= l3) && (l2 >= l3) && (l4 >= l3) && (flg == false))
            {
                l3 = l4;
                move_point_7_8(pntinside);
                l4 = dist(hull->at(m), hull->at((m + 1) % hull->size()));
                add_point_pntinside(pntinside, hull->at(m), hull->at((m + 1) % hull->size()));
                flg = true;
            }
            if ((l1 >= l2) && (l3 >= l2) && (l4 >= l2) && (flg == false))
            {
                l2 = l3;
                move_point_5_6(pntinside);
                l3 = l4;
                move_point_7_8(pntinside);
                l4 = dist(hull->at(m), hull->at((m + 1) % hull->size()));
                add_point_pntinside(pntinside, hull->at(m), hull->at((m + 1) % hull->size()));
                flg = true;
            }
            if ((l2 >= l1) && (l3 >= l1) && (l4 >= l1) && (flg == false))
            {
                l1 = l2;
                move_point_3_4(pntinside);
                l2 = l3;
                move_point_5_6(pntinside);
                l3 = l4;
                move_point_7_8(pntinside);
                l4 = dist(hull->at(m), hull->at((m + 1) % hull->size()));
                add_point_pntinside(pntinside, hull->at(m), hull->at((m + 1) % hull->size()));
                flg = true;
            }
        }
    }
}
