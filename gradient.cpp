#include <opencv2/core/core.hpp>
#include <vector>
#include "structures_point.h"

float module(const point<double>& p) {
    return p.i * p.i + p.j * p.j;
}

std::vector <std::vector < point <double>>> gradient(const std::vector <std::vector < double>> &monochorome_img,
                                                     const int &img_rows, const int &img_cols, const double &noise_limit)
{
    std::vector <std::vector < point <double>>> gradimg(img_rows);
    int i, j;
    double maxgrad = 0;
    for (i = 0; i < img_rows; i++)
    {
        gradimg[i].resize(img_cols);
    }
    for (i = 1; i < img_rows - 1; i++)
    {
        const std::vector < double> &monochorome_img_i = monochorome_img[i];
        const std::vector < double> &monochorome_img_i_plus = monochorome_img[i+1];
        const std::vector < double> &monochorome_img_i_minus = monochorome_img[i];
        std::vector < point <double>> &gradimg_i = gradimg[i];
        for (j = 1; j < img_cols - 1; j++)
        {
            point <double> &gradimg_ij = gradimg_i[j];
            gradimg_ij.i = monochorome_img_i_plus[j-1] + 2* monochorome_img_i_plus[j] + monochorome_img_i_plus[j+1]
                            - monochorome_img_i_minus[j-1] - 2*monochorome_img_i_minus[j] - monochorome_img_i_minus[j+1];
            gradimg_ij.j = monochorome_img_i_minus[j+1] + 2*monochorome_img_i[j+1] + monochorome_img_i_plus[j+1]
                            - monochorome_img_i_minus[j-1] - 2*monochorome_img_i[j-1] - monochorome_img_i_plus[j-1];
            if (sqrt(module(gradimg_ij)) > maxgrad)
                maxgrad = sqrt(module(gradimg_ij));
        }
    }
    for (i = 0; i < img_rows; i++)
    {
        std::vector < point <double>> &gradimg_i = gradimg[i];
        for (j = 0; j < img_cols; j++)
        {
            point <double> &gradimg_ij = gradimg_i[j];
            gradimg_ij.i = gradimg_ij.i / maxgrad;
            gradimg_ij.j = gradimg_ij.j / maxgrad;
            if (sqrt(module(gradimg_ij)) < noise_limit)
            {
                gradimg_ij.i = 0;
                gradimg_ij.j = 0;
            }
        }
    }
    return gradimg;
}

