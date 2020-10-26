#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <vector>
#include <algorithm>
#include "structures_and_basicfun.h"

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

void framing_window(std::vector <std::vector < grad>> mat, int a, int b, cv::Mat *img,int &lft,int &rt,int &up,int &down)
{
    std::vector <std::vector < bool>> wind(a);
    int i, j, m, k;
    int obl = 50;
    bool x, y;
    for (i = 0; i < a; i++)
    {
        wind[i].resize(b);
    }
    lft = b - 1;
    rt = 0;
    up = a - 1;
    down = 0;
    for (i = 0; i < a; i++)
    {
        for (j = 0; j < b; j++)
        {
            wind[i][j] = false;
            x = false;
            y = false;
            for (m = std::max(0, i - a / obl); m < std::min(a - 1, i + a / obl); m++)
            {
                for (k = std::max(0, j - b / obl); k < std::min(b - 1, j + b / obl); k++)
                {
                    if(abs(mat[m][k].i) > 3*abs(mat[m][k].j))
                    {
                            x = true;
                    }
                    if(abs(mat[m][k].j) > 3*abs(mat[m][k].i))
                    {
                            y = true;
                    }
                }
            }
            wind[i][j] = x * y;
            if (wind[i][j] == true)
            {
              if (j < lft)
                    lft = j;
                if (j > rt)
                    rt = j;
                if (i < up)
                    up = i;
               if (i > down)
                    down = i;
             }
        }
    }
}
