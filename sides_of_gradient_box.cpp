#include <opencv2/core/core.hpp>
#include <vector>
#include "structures_point.h"

void sides_of_gradient_box(int &lft, int &rt, int &up, int &down, std::vector <std::vector < point <double>>> gradient_matrix, int img_rows, int img_cols)
{
    std::vector <std::vector < bool>> wind(img_rows);
    int i, j, m, k;
    int obl = 50;
    bool x, y;
    for (i = 0; i < img_rows; i++)
    {
        wind[i].resize(img_cols);
    }
    lft = img_cols - 1;
    rt = 0;
    up = img_rows - 1;
    down = 0;
    for (i = 0; i < img_rows; i++)
    {
        for (j = 0; j < img_cols; j++)
        {
            wind[i][j] = false;
            x = false;
            y = false;
            for (m = std::max(0, i - img_rows / obl); m < std::min(img_rows - 1, i + img_rows / obl); m++)
            {
                for (k = std::max(0, j - img_cols / obl); k < std::min(img_cols - 1, j + img_cols / obl); k++)
                {
                    if(abs(gradient_matrix[m][k].i) > 3*abs(gradient_matrix[m][k].j))
                    {
                            x = true;
                    }
                    if(abs(gradient_matrix[m][k].j) > 3*abs(gradient_matrix[m][k].i))
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
