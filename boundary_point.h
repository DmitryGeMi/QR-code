#ifndef BOUNDARY_POINT_H
#define BOUNDARY_POINT_H

#include <opencv2/core/core.hpp>
#include <vector>
#include "structures_point.h"

int first_operator(int &i, const bool &first_operation);
int second_operator(int &j, const bool &second_operation);
void boundary_point_one_side(std::vector <point <int>> &pnt, const cv::Mat &img, const int &threshold,
                             const int &begin_first, const int &begin_second,
                             const int &end_first, const int &end_second,
                             const bool &first_operation, const bool &second_operation, const bool &is_vect);
std::vector <point <int>> boundary_point(const cv::Mat &img, int threshold);

#endif
