#include <QJsonObject>
#include <QJsonArray>
#include "mark_candidate_for_barcode.h"

void connect_parameters(double &noise_limit, sgb_param &param, const QJsonObject &obj)
{
    if(obj["gradient_parameters"].toObject()["noise_limit"].isDouble() != true)
        throw std::runtime_error("No or incorrect noise_limit");
    noise_limit = obj["gradient_parameters"].toObject()["noise_limit"].toDouble();

    QJsonObject obj_sgb_param = obj["mark_candidate_for_barcode_parameters"].toObject();

    if(obj_sgb_param["hog_step_in_degree"].isDouble() != true)
        throw std::runtime_error("No or incorrect hog_step_in_degree");
    param.hog_step_in_degree = obj_sgb_param["hog_step_in_degree"].toInt();

    if(obj_sgb_param["inaccuracy_perpendicular"].isDouble() != true)
        throw std::runtime_error("No or incorrect inaccuracy_perpendicular");
    param.inaccuracy_perpendicular = obj_sgb_param["inaccuracy_perpendicular"].toInt();

    if(obj_sgb_param["window_size"].isDouble() != true)
        throw std::runtime_error("No or incorrect window_size");
    param.window_size = obj_sgb_param["window_size"].toInt();

    if(obj_sgb_param["filter_peaks_hog"].isDouble() != true)
        throw std::runtime_error("No or incorrect filter_peaks_hog");
    param.filter_peaks_hog = obj_sgb_param["filter_peaks_hog"].toInt();
}

void _convert_point_in_QJsonArray(QJsonArray &pnt, const point <int> &point_intersection)
{
    pnt.push_back(point_intersection.i);
    pnt.push_back(point_intersection.j);
}

void _write_one_point(QJsonObject &obj_output, const QString key, const point <int> &point_intersection)
{
    QJsonArray pnt;
    _convert_point_in_QJsonArray(pnt, point_intersection);
    obj_output.insert(key, pnt);
}

void write_ang_barcode(QJsonObject &obj_output, const std::vector<point <int>> &point_intersection)
{
    if (point_intersection.size() != 4)
        throw std::runtime_error("Incorrect quantity point_intersection");
    _write_one_point(obj_output, "first point", point_intersection[0]);
    _write_one_point(obj_output, "second point", point_intersection[1]);
    _write_one_point(obj_output, "thrid point", point_intersection[2]);
    _write_one_point(obj_output, "fourth point", point_intersection[3]);
}
