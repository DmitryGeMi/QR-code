#ifndef GRADIENT_H
#define GRADIENT_H

#include <opencv2/core/core.hpp>
#include <vector>
#include "structures_point.h"

std::vector <std::vector < point <double>>> gradient(std::vector <std::vector < double>> mat, int a, int b);
void framing_window(std::vector <std::vector < point <double>>> mat, int a, int b, cv::Mat *img,int &lft,int &rt,int &up,int &down);

#endif
