#include <opencv2/core/core.hpp>
#include <vector>
#include "structures_point.h"

void framing_window(std::vector <std::vector < point <double>>> mat, int a, int b, cv::Mat *img,int &lft,int &rt,int &up,int &down)
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
