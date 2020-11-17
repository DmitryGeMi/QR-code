#include <opencv2/core/core.hpp>
#include <vector>

void create_img_marker(cv::Mat &new_img, const std::vector<int> &max_comp, int coef_compressive)
{

    for (int i = 0; i < new_img.rows; i++)
    {
        uchar* line = new_img.data + i * new_img.step;
        for (int j = 0; j < new_img.cols; j++)
        {
             line[j] = 0;
        }
    }
    for (int k = 1; k < max_comp.size(); k +=2)
    {
        new_img.at<uchar>(max_comp[k] * coef_compressive, max_comp[k + 1] * coef_compressive) = 255;
    }
}
