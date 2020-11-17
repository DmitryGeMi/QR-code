#ifndef TWO_PEAKS_OF_HOG_H
#define TWO_PEAKS_OF_HOG_H

#include "structures_point.h"

point<int> two_peaks_of_hog (const std::vector  <int> &hog, const int &param_filter_hog);
bool hog_perpendicular_two_main_directions(const point <int> &two_peaks, const int hog_size, const int &inaccuracy_perpendicular);

#endif
