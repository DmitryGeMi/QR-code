#include <opencv2/core/core.hpp>
#include <vector>

void convert_rgb_in_monochrome(cv::Mat img, std::vector <std::vector < double>> &matrix)
{
    for (int i = 0; i < img.rows; i++)
    {
        for (int j = 0; j < img.cols; j++)
        {
             matrix[i][j] = (img.at<cv::Vec3b>(i, j)[0] + img.at<cv::Vec3b>(i, j)[1] + img.at<cv::Vec3b>(i, j)[2]) / 3;
        }
    }
}
