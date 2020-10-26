#include <opencv2/highgui/highgui.hpp>

#include<convert_rgb_in_monochrome.h>
#include "convex_hull.h"
#include "makeWhite_outside_rect.h"
#include "structures_point.h"
#include "basicfun.h"
#include "simplifying_hull.h"
#include "finding_corner_points.h"
#include "framing_window.h"
#include "gradient.h"
#include "make_img_from_gradient.h"
#include "boundary_point.h"

int  main(int argc, char* argv[])
{
    std::string path = std::string(argv[1]);
    cv::Mat img = cv::imread(path);
    int i = 0, j = 0, threshold = 60;
    int lft = img.cols - 1, rt = 0, up = img.rows - 1, down = 0;
    std::vector <point <int>> pnt;
    std::vector <point <int>> hull;
    point <int> pntinside[8];

    std::vector <std::vector < double>> matrix(img.rows);
    for (i = 0; i < img.rows; i++)
        matrix[i].resize(img.cols);
    convert_rgb_in_monochrome(img, matrix);

    std::vector <std::vector < point <double>>> g(img.rows);
    for (i = 0; i < img.rows; i++)
        g[i].resize(img.cols);
    g = gradient(matrix, img.rows, img.cols);

    cv::Mat imggrad(img.rows, img.cols, CV_8UC1);
    make_img_from_gradient(&imggrad, g);
    framing_window(g, img.rows, img.cols, &img, lft, rt, up, down);
    makeWhite_outside_rect( &img, lft, rt, up, down);
    boundary_point(&pnt, &img, threshold);
    hull = convex_hull(pnt);
    simplifying_hull(&hull);
    finding_corner_points(&hull, pntinside);
    paint_angles(&img, pntinside);
    imwrite("res.jpg", img);
    imwrite("imggrad.jpg", imggrad);
    imshow("Gradient", imggrad);
    imshow("Display Window", img);
    cv::waitKey(0);
    return 0;
}
