#include <opencv2/core/core.hpp>

void compressive_img_candidate_for_barcode(cv::Mat &compressed_marker_grad, const cv::Mat &marker_grad, const int coef_compressive)
{
for (int i = 0; i < compressed_marker_grad.rows; i ++)
{
    uchar *pointer_marker_grad = marker_grad.data + i * coef_compressive * marker_grad.step;
    uchar *pointer_comp_img = compressed_marker_grad.data + i * compressed_marker_grad.step;
    for (int j = 0; j < compressed_marker_grad.cols; j ++)
    {
        pointer_comp_img[j] = pointer_marker_grad[j * coef_compressive];
    }
}
}
