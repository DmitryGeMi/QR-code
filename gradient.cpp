#include <opencv2/core/core.hpp>
#include <vector>
#include "structures_point.h"

float module(const point<double>& p) {
    return p.i * p.i + p.j * p.j;
}

std::vector <std::vector < point <double>>> gradient(const std::vector <std::vector < double>> &monochorome_img,
                                                     const int &img_rows, const int &img_cols, const int &noise_limit)
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
        for (j = 1; j < img_cols - 1; j++)
        {
            gradimg[i][j].i = monochorome_img[i+1][j-1] + 2* monochorome_img[i+1][j] + monochorome_img[i+1][j+1]
                            - monochorome_img[i-1][j-1] - 2*monochorome_img[i-1][j] - monochorome_img[i-1][j+1];
            gradimg[i][j].j = monochorome_img[i-1][j+1] + 2*monochorome_img[i][j+1] + monochorome_img[i+1][j+1]
                            - monochorome_img[i-1][j-1] - 2*monochorome_img[i][j-1] - monochorome_img[i+1][j-1];
            if (sqrt(module(gradimg[i][j])) > maxgrad)
                maxgrad = sqrt(module(gradimg[i][j]));
        }
    }
    for (i = 0; i < img_rows; i++)
    {
        for (j = 0; j < img_cols; j++)
        {
            gradimg[i][j].i = gradimg[i][j].i / maxgrad;
            gradimg[i][j].j = gradimg[i][j].j / maxgrad;
            if (sqrt(module(gradimg[i][j])) < 0.3)
            {
                gradimg[i][j].i = 0;
                gradimg[i][j].j = 0;
            }
        }
    }
    return gradimg;
}

