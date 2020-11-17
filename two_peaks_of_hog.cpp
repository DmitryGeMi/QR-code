#include <cstdlib>
#include <vector>
#include <stdexcept>
#include "structures_point.h"


point<int> two_peaks_of_hog (const std::vector  <int> &hog, const int &param_filter_hog)
{
    point <int> result;
    result.i = -1;
    result.j = -1;
    const int cnst = hog.size();
    int max1_in_slide = 0;
    int max2_in_slide = 0;
    int sum = 0;
    for (int k = 0; k < cnst; k++)
    {
        sum = hog[(k - 1)%cnst] + 2*hog[k] + hog[(k + 1)%cnst];
        if ((sum > max1_in_slide)&&(sum > param_filter_hog))
        {
            max1_in_slide = sum;
            result.i = k;
        }
    }
    for (int k = 0; k < cnst; k++)
    {
        if ((abs(k - result.i) > 2)&&(abs(k - result.i - cnst)%cnst > 3)&&(abs(k - result.i + cnst)% cnst > 2))
            sum = hog[(k - 1)%cnst] + 2*hog[k] + hog[(k + 1)%cnst];
        else
            sum = 0;
        if ((sum > max2_in_slide)&&(sum > param_filter_hog))
        {
            max2_in_slide = sum;
            result.j = k;
        }
    }
    return result;
}

bool hog_perpendicular_two_main_directions(const point <int> &two_peaks, const int hog_size, const int &inaccuracy_perpendicular)
{
    if (inaccuracy_perpendicular >= hog_size)
        throw std::runtime_error("Incorrect input inaccuracy_perpendicular");
    if ((two_peaks.i == -1)||(two_peaks.j == -1))
        return false;
    const int dist = abs(two_peaks.i - two_peaks.j);
    if ((dist >= hog_size/2 - inaccuracy_perpendicular)&&(dist <= hog_size/2 + inaccuracy_perpendicular))
        return true;
    else
        return false;
}
