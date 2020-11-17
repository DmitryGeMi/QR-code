#include <opencv2/core/core.hpp>
#include <vector>

std::vector <std::vector < double>> convert_in_monochrome(const cv::Mat &img)
{
    std::vector <std::vector<double> > monochrome_img(img.rows);
    for (int i = 0; i < img.rows; i++)
        monochrome_img[i].resize(img.cols);
    const int img_channels = img.channels();
    for (int i = 0; i < img.rows; i++)
    {
        std::vector<double> &monochrome_img_i = monochrome_img[i];
        uchar* line = img.data + i * img.step;
        for (int j = 0; j < img.cols; j++)
        {
            double &monochrome_img_ij = monochrome_img_i[j];
            monochrome_img_ij = 0;
            for (int c = 0; c < img_channels; c++)
            {
                monochrome_img_ij = monochrome_img_ij + line[j*img_channels+c];
            }
            monochrome_img_ij = monochrome_img_ij / img_channels;
        }
    }
    return monochrome_img;
}
