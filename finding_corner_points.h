#ifndef FINDING_CORNER_POINTS_H
#define FINDING_CORNER_POINTS_H

#include <opencv2/core/core.hpp>
#include <vector>
#include "structures_point.h"

void add_point_pntinside(point <int> *pntinside, const point <int> &point1, const point <int> &point2);
void move_point(point <int> *pntinside, const int &ind);
void find_corner_points(point <int> *pntinside, const std::vector <point <int>> &hull);
std::vector<point <int>> find_corners_intersections(point <int> *pntinside);
void paint_corners_intersections(cv::Mat *img, std::vector<point<int>> point_intersection);

#endif
