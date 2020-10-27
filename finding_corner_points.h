#ifndef FINDING_CORNER_POINTS_H
#define FINDING_CORNER_POINTS_H

#include <opencv2/core/core.hpp>
#include <vector>
#include "structures_point.h"

void add_point_pntinside(point <int> *pntinside, point <int> point1, point <int> point2);
void move_point(point <int> *pntinside, int ind);
void find_corner_points(std::vector <point <int>> *hull, point <int> *pntinside);
void paint_angles(cv::Mat *img, point <int> *pntinside);

#endif
