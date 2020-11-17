#include <opencv2/highgui/highgui.hpp>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QFile>

#include "convert_in_monochrome.h"
#include "convex_hull.h"
#include "makeWhite_outside_rect.h"
#include "structures_point.h"
#include "basic_geometry.h"
#include "simplify_hull.h"
#include "finding_corner_points.h"
#include "mark_candidate_for_barcode.h"
#include "gradient.h"
#include "make_img_from_gradient.h"
#include "boundary_point.h"
#include "structures_four_directions.h"
#include "sides_framework_white_pixels.h"
#include "compressive_img_candidate_for_barcode.h"
#include "ccl_algorithm.h"
#include "create_img_marker.h"
#include "input_parameters_output_barcode_ang.h"

#include <stdexcept>

#include <iostream>

int  main(int argc, char* argv[])
{
    if (argc == 3)
        throw std::runtime_error("No input data");

    std::string img_path;
    img_path = std::string(argv[1]);
    cv::Mat img = cv::imread(img_path);
    if (img.type() != CV_8UC3)
        throw std::runtime_error("Incorrect input image");

    QString filename = QString::fromStdString(std::string(argv[2]));
    QFile file(filename);
    if (file.open(QFile::ReadOnly) != true)
        throw std::runtime_error("No input parameters");
    QByteArray file_array = file.readAll();
    file.close();
    QJsonDocument doc_param = QJsonDocument::fromJson(file_array);
    QJsonObject obj = doc_param.object();

    double noise_limit;
    sgb_param param;
    connect_parameters(noise_limit, param, obj);

    std::vector <std::vector<double> > monochorome_img = convert_in_monochrome(img);
    std::vector <std::vector<point <double>>> grad = gradient(monochorome_img, img.rows, img.cols, noise_limit);

    cv::Mat imggrad(img.rows, img.cols, CV_8UC1);
    make_img_from_gradient(imggrad, grad);

    four_directions dir;
    dir.left = img.cols - 1, dir.right = 0, dir.up = img.rows - 1, dir.down = 0;


    param.step_canculations_in_wind = std::min(img.rows / param.window_size, img.cols / param.window_size) - 1;
    cv::Mat candidate_imggrad_marker(img.rows, img.cols, CV_8UC1);
    mark_candidate_for_barcode(candidate_imggrad_marker, grad, img.rows, img.cols, param);

    cv::Mat comressed_imggrad_marker(img.rows/param.step_canculations_in_wind,
                                     img.cols/param.step_canculations_in_wind, CV_8UC1);
    compressive_img_candidate_for_barcode(comressed_imggrad_marker, candidate_imggrad_marker, param.step_canculations_in_wind);

    std::vector <std::vector<int> > copy_comp_img;

    ccl_algorithm(copy_comp_img,  comressed_imggrad_marker);

    std::vector<std::vector<int>> comps;

    create_set_of_components(comps, copy_comp_img);
    std::vector<int> max_comp = find_max_comp(comps);

    cv::Mat imggrad_marker(img.rows, img.cols, CV_8UC1);


    create_img_marker(imggrad_marker, max_comp, param.step_canculations_in_wind);


    sides_framework_white_pixels(dir, imggrad_marker);
    makeWhite_outside_rect(img, dir.left, dir.right, dir.up, dir.down);

    const int threshold = 60;
    std::vector<point<int>> pnt = boundary_point(img, threshold);
    std::vector<point<int>> hull = convex_hull(pnt);
    double parameter_delete_pnt = 0.997;
    simplify_hull(hull, parameter_delete_pnt);

    point<int> pntinside[8];
    find_corner_points(pntinside, hull);

    std::vector<point <int>> point_intersection;
    point_intersection = find_corners_intersections(pntinside);
    paint_corners_intersections(&img, point_intersection);

    QFile output(QString::fromStdString(std::string(argv[3])));
    if (output.open(QFile::WriteOnly) != true)
        throw std::runtime_error("No output address");
    QJsonObject obj_output;
    write_ang_barcode(obj_output, point_intersection);
    QJsonDocument doc_output(obj_output);
    output.write(doc_output.toJson());
    output.close();

    imwrite("res.jpg", img);
    imwrite("imggrad.jpg", imggrad);
    imwrite("marker.jpg", imggrad_marker);
    imwrite("marker.jpg", comressed_imggrad_marker);
//    imshow("Comressed gradient marker", comressed_imggrad_marker);
//    imshow("Candidate gradient marker", candidate_imggrad_marker);
//    imshow("Gradient marker", imggrad_marker);
//    imshow("Gradient", imggrad);
//    imshow("Display Window", img);
    cv::waitKey(0);
    return 0;
}
