#include <math.h>
#include <stdexcept>
#include <vector>
#include <iostream>
#include <iomanip>
#include <stdexcept>


int hog_index(const double &grd_coordinate_x, const double &grd_coordinate_y, const int &hog_step_in_degree)
{
    if ((360 % hog_step_in_degree) != 0)
        throw std::runtime_error("Incorrect input hog_step_in_degree in hog_index");
    double cnst = 180/hog_step_in_degree/M_PI;
    return (int)((atan2(grd_coordinate_x, grd_coordinate_y) + M_PI)*cnst);
}

void hog_normalization(std::vector <int> &hog_nornal, const int &max_hog_elem, const int &num_stars)
{
    for(int i = 0; i < hog_nornal.size(); i++)
        hog_nornal[i] = (int)(hog_nornal[i] * num_stars / max_hog_elem);
}

std::vector <int> hog_unification_opposite_directions(const std::vector <int> &hog, const int &hog_step_in_degree)
{
    if ((360 % (2*hog_step_in_degree)) != 0)
        throw std::runtime_error("Incorrect input hog_step_in_degree in hog_unification_opposite_directions");
    std::vector <int> hog_unif(hog.size()/2, 0);
    for(int i = 0; i < hog_unif.size(); i++)
        hog_unif[i] = hog[i] + hog[i + hog.size()/2];
    return hog_unif;
}

void hog_display_view_stars(const std::vector <int> &hog, const int &hog_step_in_degree, const int &num_stars)
{
    if (num_stars < 1)
        throw std::runtime_error("Incorrect num_stars");
    int max_hog_elem = 0;
    for(int i = 0; i < hog.size(); i++)
    {
        if (hog[i] > max_hog_elem)
            max_hog_elem = hog[i];
    }
    std::vector <int> hog_normal = hog;
    if (max_hog_elem > num_stars)
    {
        hog_normalization(hog_normal, max_hog_elem, num_stars);
    }
    for(int i = 0; i < hog_normal.size(); i++)
    {
        std::cout << std::setw(3) << i * hog_step_in_degree << "-" <<
                     std::setw(3) << (i + 1) * hog_step_in_degree << " ";
        for (int j = 0; j < hog_normal[i]; j++)
            std::cout << "*";
        std::cout << std::endl;
    }
}
