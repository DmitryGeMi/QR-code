#include <opencv2/core/core.hpp>
#include "structures_point.h"

void make_img_from_gradient(cv::Mat *imggrad, std::vector <std::vector < point <double> >> g)
{
    for (int i = 0; i < imggrad->rows; i++)
        for (int j = 0; j < imggrad->cols; j++)
           imggrad->at<uchar>(i, j) = sqrt(g[i][j].i*g[i][j].i + g[i][j].j*g[i][j].j) * 255;
}
