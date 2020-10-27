#ifndef GRADIENT_H
#define GRADIENT_H

#include <opencv2/core/core.hpp>
#include <vector>
#include "structures_point.h"

float module(const point<int>& p);
std::vector <std::vector < point <double>>> gradient(const std::vector <std::vector < double>> &monochorome_img, const int &img_rows,
                                                     const int &img_cols, const int &noise_limit);

#endif
