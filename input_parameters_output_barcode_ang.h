#ifndef CONNECT_PARAMETERS_H
#define CONNECT_PARAMETERS_H

#include <QJsonObject>
#include <vector>
#include "mark_candidate_for_barcode.h"

void connect_parameters(double &noise_limit, sgb_param &param,const QJsonObject &obj);
void write_ang_barcode(QJsonObject &obj_output, const std::vector<point <int>> &point_intersection);

#endif
