#include <opencv2/core/core.hpp>
#include "structures_point.h"
#include "basic_geometry.h"

void make_img_from_gradient(cv::Mat &imggrad, const std::vector <std::vector < point <double> >>& g)
{
    if (imggrad.type() != CV_8UC1)
            throw std::runtime_error("Incorrect input image");
    for (int i = 0; i < imggrad.rows; i++)
        for (int j = 0; j < imggrad.cols; j++)
            imggrad.at<uchar>(i, j) = hypotenuse(g[i][j].i, g[i][j].j) * 255;
}
