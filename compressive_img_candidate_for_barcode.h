#ifndef COMPRESSIVE_IMG_CANDIDATE_FOR_BARCODE_H
#define COMPRESSIVE_IMG_CANDIDATE_FOR_BARCODE_H

#include <opencv2/core/core.hpp>

void compressive_img_candidate_for_barcode(cv::Mat &compressed_marker_grad, const cv::Mat &marker_grad, const int coef_compressive);

#endif
