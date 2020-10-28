#ifndef FRAMING_WINDOW_H
#define FRAMING_WINDOW_H

#include <opencv2/core/core.hpp>
#include <vector>
#include "structures_point.h"

void sides_of_gradient_box(int &lft, int &rt, int &up, int &down,
                           const  std::vector <std::vector < point <double>>> &gradient_matrix,
                           const int &img_rows, const int &img_cols, const int &vicinity_size);

#endif
