#include "boundary_point.h"

void boundary_point(std::vector <point> *pnt, cv::Mat *img)
{
    point point;
    bool flg = false;
    int i, j, m;
    for (i = 0; i < img->rows; i++)
        for (j = 0; j < img->cols; j++)
        {
            if ((img->at<cv::Vec3b>(i, j)[0] < 60) && (img->at<cv::Vec3b>(i, j)[1] < 60) && (img->at<cv::Vec3b>(i, j)[2] < 60))
            {
                point.i = i;
                point.j = j;
                pnt->push_back(point);
                break;
            }
        }
    for (j = img->cols - 1; j > 0; j--)
        for (i = 0; i < img->rows; i++)
        {
            if ((img->at<cv::Vec3b>(i, j)[0] < 60) && (img->at<cv::Vec3b>(i, j)[1] < 60) && (img->at<cv::Vec3b>(i, j)[2] < 60))
            {
                for (m = 0; m < pnt->size(); m++)
                {
                    if ((pnt->at(m).i == i) && (pnt->at(m).j == j))
                    {
                        flg = true;
                    }
                }
                if (flg == false)
                {
                    point.i = i;
                    point.j = j;
                    pnt->push_back(point);
                }
                flg = false;
                break;
            }
        }
    for (j = 0; j < img->cols; j++)
        for (i = img->rows - 1; i > 0; i--)
        {
            if ((img->at<cv::Vec3b>(i, j)[0] < 60) && (img->at<cv::Vec3b>(i, j)[1] < 60) && (img->at<cv::Vec3b>(i, j)[2] < 60))
            {
                for (m = 0; m < pnt->size(); m++)
                {
                    if ((pnt->at(m).i == i) && (pnt->at(m).j == j))
                    {
                        flg = true;
                    }
                }
                if (flg == false)
                {
                    point.i = i;
                    point.j = j;
                    pnt->push_back(point);
                }
                flg = false;
                break;
            }
        }
    for (i = img->rows - 1; i > 0; i--)
        for (j = img->cols - 1; j > 0; j--)
        {
            if ((img->at<cv::Vec3b>(i, j)[0] < 60) && (img->at<cv::Vec3b>(i, j)[1] < 60) && (img->at<cv::Vec3b>(i, j)[2] < 60))
            {
                for (m = 0; m < pnt->size(); m++)
                {
                    if ((pnt->at(m).i == i) && (pnt->at(m).j == j))
                    {
                        flg = true;
                    }
                }
                if (flg == false)
                {
                    point.i = i;
                    point.j = j;
                    pnt->push_back(point);
                }
                flg = false;
                break;
            }
        }
}
