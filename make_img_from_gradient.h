#ifndef MAKE_IMG_FROM_GRADIENT_H
#define MAKE_IMG_FROM_GRADIENT_H

#include <opencv2/core/core.hpp>
#include "structures_point.h"

void make_img_from_gradient(cv::Mat *imggrad, std::vector <std::vector < point <double>>> g);

#endif
