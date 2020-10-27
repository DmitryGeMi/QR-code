#ifndef CONVERT_RGB_IN_MONOCHROME_H
#define CONVERT_RGB_IN_MONOCHROME_H

#include <opencv2/core/core.hpp>
#include <vector>

void convert_rgb_in_monochrome(const cv::Mat& img, std::vector <std::vector < double>> &matrix);

#endif
