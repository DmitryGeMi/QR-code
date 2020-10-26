#include <opencv2/core/core.hpp>
#include <vector>
#include "structures_point.h"

std::vector <std::vector < grad>> gradient(std::vector <std::vector < double>> mat, int a, int b)
{
    std::vector <std::vector < grad>> gradimg(a);
    int i, j;
    double maxgrad = 0;
    for (i = 0; i < a; i++)
    {
        gradimg[i].resize(b);
    }
    for (i = 1; i < a - 1; i++)
    {
        for (j = 1; j < b - 1; j++)
        {
            gradimg[i][j].i = mat[i+1][j-1] + 2* mat[i+1][j] + mat[i+1][j+1] - mat[i-1][j-1] - 2*mat[i-1][j] - mat[i-1][j+1];
            gradimg[i][j].j = mat[i-1][j+1] + 2*mat[i][j+1] + mat[i+1][j+1] - mat[i-1][j-1] - 2*mat[i][j-1] - mat[i+1][j-1];
            if (sqrt(gradimg[i][j].i*gradimg[i][j].i + gradimg[i][j].j*gradimg[i][j].j) > maxgrad)
                maxgrad = sqrt(gradimg[i][j].i*gradimg[i][j].i + gradimg[i][j].j*gradimg[i][j].j);
        }
    }
    for (i = 0; i < a; i++)
    {
        for (j = 0; j < b; j++)
        {
            gradimg[i][j].i = gradimg[i][j].i / maxgrad;
            gradimg[i][j].j = gradimg[i][j].j / maxgrad;
            if (sqrt(gradimg[i][j].i*gradimg[i][j].i + gradimg[i][j].j*gradimg[i][j].j) < 0.3)
            {
                gradimg[i][j].i = 0;
                gradimg[i][j].j = 0;
            }
        }
    }
    return gradimg;
}

