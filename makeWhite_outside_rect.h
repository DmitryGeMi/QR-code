#ifndef MAKEWHITE_OUTSIDE_RECT_H
#define MAKEWHITE_OUTSIDE_RECT_H

#include <opencv2/core/core.hpp>

void makeWhite_outside_rect(cv::Mat& img,int lft,int rt,int up,int down);
void makeWhite(cv::Mat& img, int i, int j);

#endif
