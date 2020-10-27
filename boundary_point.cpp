#include <opencv2/core/core.hpp>
#include <vector>
#include "structures_point.h"

int first_operator(int &i, const bool &first_operation)
{
    if (first_operation == true)
        i++;
    else
        i--;
}
int second_operator(int &j, const bool &second_operation)
{
    if (second_operation == true)
        j++;
    else
        j--;
}
void boundary_point_one_side(std::vector <point <int>>& pnt, const cv::Mat &img,const int &threshold,
                             const int &begin_first, const int &begin_second,
                             const int &end_first, const int &end_second,
                             const bool &first_operation, const  bool &second_operation, const bool &is_vect)
{

    point <int> auxiliary_point;
    bool flg = false;
    int i, j, m;
    for (i = begin_first; (((i < end_first)*first_operation)||((i > end_first)*!first_operation)); first_operator(i, first_operation))
        for (j = begin_second; (((j < end_second)*second_operation)||((j > end_second)*!second_operation)); second_operator(j, second_operation))
        {
           if(is_vect == true)
           {
            if ((img.at<cv::Vec3b>(i, j)[0] < threshold) && (img.at<cv::Vec3b>(i, j)[1] < threshold) && (img.at<cv::Vec3b>(i, j)[2] < threshold))
            {
                for (m = 0; m < pnt.size(); m++)
                {
                    if ((pnt.at(m).i == i) && (pnt.at(m).j == j))
                    {
                        flg = true;
                    }
                }
                if (flg == false)
                {
                    auxiliary_point.i = i;
                    auxiliary_point.j = j;
                    pnt.push_back(auxiliary_point);
                }
                flg = false;
                break;
            }
           }
           else
           {
               if ((img.at<cv::Vec3b>(j, i)[0] < threshold) && (img.at<cv::Vec3b>(j, i)[1] < threshold) && (img.at<cv::Vec3b>(j, i)[2] < threshold))
               {
                   for (m = 0; m < pnt.size(); m++)
                   {
                       if ((pnt.at(m).i == j) && (pnt.at(m).j == i))
                       {
                           flg = true;
                       }
                   }
                   if (flg == false)
                   {
                       auxiliary_point.i = j;
                       auxiliary_point.j = i;
                       pnt.push_back(auxiliary_point);
                   }
                   flg = false;
                   break;
               }
           }
        }
}

std::vector <point <int>> boundary_point(const cv::Mat &img,int threshold)
{
    std::vector <point <int>> pnt;
    boundary_point_one_side(pnt, img, threshold,
                                 0, 0,
                                 img.rows, img.cols,
                                 true, true, true);
    boundary_point_one_side(pnt, img, threshold,
                                 img.cols - 1, 0,
                                 0, img.rows,
                                 false, true, false);
    boundary_point_one_side(pnt, img, threshold,
                                 0, img.rows - 1,
                                 img.cols, 0,
                                 true, false, false);
    boundary_point_one_side(pnt, img, threshold,
                                 img.rows - 1, img.cols - 1,
                                 0, 0,
                                 false, false, true);
    return pnt;
}
