#ifndef HOG_INDEX_H
#define HOG_INDEX_H

#include<vector>

int hog_index(const double &grd_coordinate_x, const double &grd_coordinate_y, const int &hog_step_in_degree);
void hog_normalization(std::vector <int> &hog, const int &max_hog_elem, const int &num_stars);
std::vector <int> hog_unification_opposite_directions(const std::vector <int> &hog, const int &hog_step_in_degree);
void hog_display_view_stars(const std::vector <int> &hog, const int &hog_step_in_degree, const int &num_stars);

#endif
