#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>
#include <string>
#include <algorithm>
#include <vector>

#include "convex_hull.h"
#include "makeWhite_outside_rect.h"
#include "structures_and_basicfun.h"
#include "simplifying_hall.h"
#include "finding_corner_points.h"
#include "gradient_and_framing_window.h"
#include "boundary_point.h"

int  main(int argc, char* argv[])
{
    std::string path = "/home/user/QRcode/" + std::string(argv[1]);
    cv::Mat img = cv::imread(path);
    cv::Mat imggrad(img.rows, img.cols, CV_8UC1);
    int i = 0, j = 0;
    int lft = img.cols - 1, rt = 0, up = img.rows - 1, down = 0;
    std::vector <point> pnt;
    std::vector <point> hull;
    point pntinside[8];
    std::vector <std::vector < double>> matrix(img.rows);
    for (i = 0; i < img.rows; i++)
    {
        matrix[i].resize(img.cols);
        for (j = 0; j < img.cols; j++)
        {
            matrix[i][j] = (img.at<cv::Vec3b>(i, j)[0] + img.at<cv::Vec3b>(i, j)[1] + img.at<cv::Vec3b>(i, j)[2]) / 3;
        }
    }
    std::vector <std::vector < grad >> g(img.rows);
    for (i = 0; i < img.rows; i++)
        g[i].resize(img.cols);
    g = gradient(matrix, img.rows, img.cols);
    for (i = 0; i < imggrad.rows; i++)
        for (j = 0; j < imggrad.cols; j++)
            imggrad.at<uchar>(i, j) = sqrt(g[i][j].i*g[i][j].i + g[i][j].j*g[i][j].j) * 255;
    framing_window(g, img.rows, img.cols, & img, lft, rt, up, down);
    makeWhite_outside_rect(& img, lft, rt, up, down);
    boundary_point(&pnt, &img);
    hull = convex_hull(pnt);
    simplifying_hall(&hull);
    finding_corner_points(&hull, pntinside);
    paint_angles(&img, pntinside);
    imwrite("res.jpg", img);
    imwrite("imggrad.jpg", imggrad);
    imshow("Gradient", imggrad);
    imshow("Display Window", img);
    cv::waitKey(0);
    return 0;
}
