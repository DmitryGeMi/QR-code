#ifndef BOUNDARY_POINT_H
#define BOUNDARY_POINT_H

#include <opencv2/core/core.hpp>
#include <vector>
#include "structures_point.h"

int first_operator(int &i, bool first_operation);
int second_operator(int &j, bool second_operation);
void boundary_point_one_side(std::vector <point <int>> &pnt, cv::Mat *img,int threshold,
                             int begin_first, int begin_second,
                             int end_first, int end_second,
                             bool first_operation, bool second_operation, bool is_vect);
void boundary_point(std::vector<point <int>>& pnt, cv::Mat *img, int threshold);

#endif
