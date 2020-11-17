#ifndef MARK_CANDIDATE_FOR_BARCODE_H
#define MARK_CANDIDATE_FOR_BARCODE_H

#include <opencv2/core/core.hpp>
#include <vector>
#include "structures_point.h"
#include "structures_four_directions.h"

using Type_input_gradient_matrix = std::vector <std::vector < point <double>>>;


struct sgb_param  //sides_of_gradient_box
{
    int window_size;
    int hog_step_in_degree;
    int inaccuracy_perpendicular;
    int filter_peaks_hog;
    int step_canculations_in_wind;
};

void mark_candidate_for_barcode(cv::Mat &marker_grad, const Type_input_gradient_matrix &gradient_matrix,
                           const int &img_rows, const int &img_cols, const sgb_param &param);

#endif
