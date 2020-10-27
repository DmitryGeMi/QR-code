#include <opencv2/core/core.hpp>
#include <vector>

std::vector <std::vector < double>> convert_in_monochrome(const cv::Mat &img)
{
    std::vector <std::vector<double> > monochrome_img(img.rows);
        for (int i = 0; i < img.rows; i++)
            monochrome_img[i].resize(img.cols);
    for (int i = 0; i < img.rows; i++)
    {
        uchar* line = img.data + i * img.step;
        for (int j = 0; j < img.cols; j++)
        {
            monochrome_img[i][j] = 0;
            for (int c = 0; c <img.channels(); c++)
            {
                monochrome_img[i][j] = monochrome_img[i][j] + line[j*img.channels()+c];
            }
            monochrome_img[i][j] = monochrome_img[i][j] / img.channels();
        }
    }
    return monochrome_img;
}
