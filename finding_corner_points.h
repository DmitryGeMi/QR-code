#ifndef FINDING_CORNER_POINTS_H
#define FINDING_CORNER_POINTS_H

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <vector>
#include "structures.h"
#include "basicfun.h"

void add_point_pntinside(point *pntinside, point point1, point point2);
void move_point_3_4(point *pntinside);
void move_point_5_6(point *pntinside);
void move_point_7_8(point *pntinside);
void finding_corner_points(std::vector <point> *hull, point *pntinside);
void paint_angles(cv::Mat *img, point *pntinside);
void paint_angles(cv::Mat *img, point *pntinside);

#endif
