#include <opencv2/highgui/highgui.hpp>

#include<convert_in_monochrome.h>
#include "convex_hull.h"
#include "makeWhite_outside_rect.h"
#include "structures_point.h"
#include "basicfun.h"
#include "simplifying_hull.h"
#include "finding_corner_points.h"
#include "sides_of_gradient_box.h"
#include "gradient.h"
#include "make_img_from_gradient.h"
#include "boundary_point.h"

int  main(int argc, char* argv[])
{
    if (argc == 1)
        return 1;

    std::string path = std::string(argv[1]);
    cv::Mat img = cv::imread(path);
    if (img.type() != CV_8UC3)
            throw std::runtime_error("Incorrect input image");

    const int threshold = 60;

    std::vector <std::vector<double> > matrix(img.rows);
    for (int i = 0; i < img.rows; i++)
        matrix[i].resize(img.cols);
    convert_rgb_in_monochrome(img, matrix);

    std::vector <std::vector<point <double>>> g(img.rows);
    for (int i = 0; i < img.rows; i++)
        g[i].resize(img.cols);
    g = gradient(matrix, img.rows, img.cols);

    cv::Mat imggrad(img.rows, img.cols, CV_8UC1);
    make_img_from_gradient(imggrad, g);

    int lft = img.cols - 1, rt = 0, up = img.rows - 1, down = 0;
    framing_window(g, img.rows, img.cols, &img, lft, rt, up, down);
    makeWhite_outside_rect(img, lft, rt, up, down);

    std::vector<point<int>> pnt;
    boundary_point(pnt, &img, threshold);

    std::vector<point<int>> hull = convex_hull(pnt);
    simplify_hull(&hull);

    point<int> pntinside[8];
    find_corner_points(&hull, pntinside);
    paint_angles(&img, pntinside);

    imwrite("res.jpg", img);
    imwrite("imggrad.jpg", imggrad);
    imshow("Gradient", imggrad);
    imshow("Display Window", img);
    cv::waitKey(0);
    return 0;
}
