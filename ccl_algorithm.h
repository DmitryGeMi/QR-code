#ifndef CCL_ALGORITHM_H
#define CCL_ALGORITHM_H

#include <opencv2/core/core.hpp>

void ccl_algorithm(std::vector<std::vector<int>>& imgcopy, const cv::Mat &img);
void create_set_of_components(std::vector<std::vector<int>>& comps, const std::vector<std::vector<int>>& imgcopy);
std::vector<int> find_max_comp(const std::vector<std::vector<int>>& comps);

#endif
