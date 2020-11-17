#include <opencv2/core/core.hpp>
#include <vector>
#include <stdexcept>
#include "structures_point.h"
#include "hog_basic_instrument.h"
#include "two_peaks_of_hog.h"
#include "mark_candidate_for_barcode.h"

void mark_candidate_for_barcode(cv::Mat &marker_grad, const  Type_input_gradient_matrix &gradient_matrix,
                           const int &img_rows, const int &img_cols, const sgb_param &param)
{
    if ((360 % (2*param.hog_step_in_degree)) != 0)
        throw std::runtime_error("Incorrect hog_step_in_degree");
    if (param.step_canculations_in_wind < 1)
        throw std::runtime_error("Incorrect step_canculations_in_wind");
    int i, j, m, k;
    for (i = 0; i < img_rows; i += param.step_canculations_in_wind)
    {
        const int wind_left_ind = i - img_rows / param.window_size;
        const int wind_right_ind = i + img_rows / param.window_size;
        uchar* line = marker_grad.data + i * marker_grad.step;
        for (j = 0; j < img_cols; j += param.step_canculations_in_wind)
        {
            bool flag = false;
            const int wind_up_ind = j - img_cols / param.window_size;
            const int wind_down_ind = j + img_cols / param.window_size;
            std::vector <int> hog(360 / param.hog_step_in_degree, 0);
            for (m = std::max(0, wind_left_ind); m < std::min(img_rows - 1, wind_right_ind); m++)
            {
                std::vector<point<double>> gm_m = gradient_matrix[m];
                for (k = std::max(0, wind_up_ind); k < std::min(img_cols - 1, wind_down_ind); k++)
                {
                    point<double> gm_mk = gm_m[k];
                    if ((gm_mk.i != 0)||(gm_mk.j != 0))
                    {
                        hog[hog_index(gm_mk.i, gm_mk.j, param.hog_step_in_degree)] ++;
                    }
                }
            }
            std::vector <int> hog_unif = hog_unification_opposite_directions(hog, param.hog_step_in_degree);
            point <int> pnt;
            pnt = two_peaks_of_hog(hog_unif, param.filter_peaks_hog);
            flag =  hog_perpendicular_two_main_directions(pnt, hog_unif.size(), param.inaccuracy_perpendicular);
            if (flag == 0)
                line[j] = 0;
            else
                line[j] = 255;
        }
    }
}
