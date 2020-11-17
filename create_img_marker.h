#ifndef CREATE_IMG_MARKER_H
#define CREATE_IMG_MARKER_H

#include <opencv2/core/core.hpp>
#include <vector>

void create_img_marker(cv::Mat &new_img, const std::vector<int> &max_comp, int coef_compressive);

#endif
