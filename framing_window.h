#ifndef FRAMING_WINDOW_H
#define FRAMING_WINDOW_H

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <vector>
#include "structures.h"

void framing_window(std::vector <std::vector < grad>> mat, int a, int b, cv::Mat *img,int &lft,int &rt,int &up,int &down);

#endif
