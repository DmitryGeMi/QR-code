#ifndef FRAMING_WINDOW_H
#define FRAMING_WINDOW_H

#include <opencv2/core/core.hpp>
#include <vector>
#include "structures_point.h"

void sides_of_gradient_box(int &lft,int &rt,int &up,int &down,std::vector <std::vector < point <double>>> gradient_matrix, int img_rows, int img_cols);

#endif
