#include <opencv2/core/core.hpp>
#include <vector>

void convert_rgb_in_monochrome(const cv::Mat& img, std::vector <std::vector < double>> &matrix)
{
    for (int i = 0; i < img.rows; i++)
    {
        uchar* line = img.data + i * img.step;
        for (int j = 0; j < img.cols; j++)
        {
            matrix[i][j] = 0;
            for (int c = 0; c <img.channels(); c++)
            {
                matrix[i][j] = matrix[i][j] + line[j*img.channels()+c];
            }
            matrix[i][j] = matrix[i][j] / img.channels();
        }
    }
}
