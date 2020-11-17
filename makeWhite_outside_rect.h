#ifndef MAKEWHITE_OUTSIDE_RECT_H
#define MAKEWHITE_OUTSIDE_RECT_H

#include <opencv2/core/core.hpp>

void makeWhite_outside_rect(cv::Mat& img,const int lft,const int rt,const int up,const int down);
void makeWhite(cv::Mat& img, const int &img_channels, const int i, const int j);

#endif
