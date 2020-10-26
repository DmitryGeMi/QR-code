#ifndef BOUNDARY_POINT_H
#define BOUNDARY_POINT_H

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <vector>
#include "structures.h"

void boundary_point(std::vector <point> *pnt, cv::Mat *img);

#endif
