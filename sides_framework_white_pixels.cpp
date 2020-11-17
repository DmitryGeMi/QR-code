#include <opencv2/core/core.hpp>
#include "structures_four_directions.h"

void sides_framework_white_pixels(four_directions &dir, const cv::Mat &marker_grad)
{
    for (int i = 0; i < marker_grad.rows; i ++)
    {
        uchar* line = marker_grad.data + i * marker_grad.step;
        for(int j = 0; j < marker_grad.cols; j++)
        {
            if (line[j] == 255)
            {
              if (j < dir.left)
                    dir.left = j;
              if (j > dir.right)
                    dir.right = j;
              if (i < dir.up)
                    dir.up = i;
              if (i > dir.down)
                    dir.down = i;
            }
        }
    }
}
