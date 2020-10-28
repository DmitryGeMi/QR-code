#include <opencv2/highgui/highgui.hpp>

#include "convert_in_monochrome.h"
#include "convex_hull.h"
#include "makeWhite_outside_rect.h"
#include "structures_point.h"
#include "basic_geometry.h"
#include "simplify_hull.h"
#include "finding_corner_points.h"
#include "sides_of_gradient_box.h"
#include "gradient.h"
#include "make_img_from_gradient.h"
#include "boundary_point.h"

int  main(int argc, char* argv[])
{
    std::string path;
    if (argc == 1)
        path = "/home/user/QRcode";
    else
        path = std::string(argv[1]);
    cv::Mat img = cv::imread(path);
    if (img.type() != CV_8UC3)
            throw std::runtime_error("Incorrect input image");

    const int threshold = 60;

    std::vector <std::vector<double> > monochorome_img = convert_in_monochrome(img);

    int noise_limit = 0.3;
    std::vector <std::vector<point <double>>> grad = gradient(monochorome_img, img.rows, img.cols, noise_limit);

    cv::Mat imggrad(img.rows, img.cols, CV_8UC1);
    make_img_from_gradient(imggrad, grad);

    int lft = img.cols - 1, rt = 0, up = img.rows - 1, down = 0;
    int vicinity_size = 50;
    sides_of_gradient_box( lft, rt, up, down,grad, img.rows, img.cols, vicinity_size);
    makeWhite_outside_rect(img, lft, rt, up, down);

    std::vector<point<int>> pnt = boundary_point(img, threshold);

    std::vector<point<int>> hull = convex_hull(pnt);
    double parameter_delete_pnt = 0.995;
    simplify_hull(hull, parameter_delete_pnt);

    point<int> pntinside[8];
    find_corner_points(pntinside, hull);
    paint_corners_intersections(&img, pntinside);

    imwrite("res.jpg", img);
    imwrite("imggrad.jpg", imggrad);
    imshow("Gradient", imggrad);
    imshow("Display Window", img);
    cv::waitKey(0);

    return 0;
}
