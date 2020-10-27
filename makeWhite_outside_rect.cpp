#include <opencv2/core/core.hpp>

void makeWhite(cv::Mat& img, int i, int j)
{
    uchar* line = img.data + i * img.step;
    for (int c = 0; c <img.channels(); c++)
    {
        line[j*img.channels()+c] = 255;
    }
}

void makeWhite_outside_rect(cv::Mat & img,int lft,int rt,int up,int down)
{
    int i,j;
    for (i = 0; i < up; i++)
        for (j = 0; j < img.cols; j++)
        {
            makeWhite(img, i, j);
        }
    for (i = up; i < down; i++)
    {
        for (j = 0; j < lft; j++)
        {
            makeWhite(img, i, j);
        }
        for (j = rt; j < img.cols; j++)
        {
            makeWhite(img, i, j);
        }
    }
    for (i = down; i < img.rows; i++)
        for (j = 0; j < img.cols; j++)
        {
            makeWhite(img, i, j);
        }
}
