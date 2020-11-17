#include <opencv2/core/core.hpp>
#include <iostream>
#include <vector>

int find_(int X, std::vector<int> const& linked)
{
    int j = X;
    while (linked[j-1] != 0)
        j = linked[j-1];
    return j;

}

void union_(int X, int Y, std::vector<int>& linked)
{
    int j = find_(X, linked);
    int k = find_(Y, linked);
    if (j != k)
        linked[k-1] = j;
}

void ccl_algorithm(std::vector<std::vector<int>>& imgcopy, const cv::Mat &img)
{
    std::vector<int> linked;
    int label = 0, B = 0, C = 0, D = 0, E = 0;
    for (int i = 0; i < img.rows; i++)
    {
        imgcopy.push_back(std::vector<int>());
        for (int j = 0; j < img.cols; j++)
            {
            if (img.at<uchar>(i, j) == 0)
            {
                imgcopy[i].push_back(0);
            }
            else
            {
                if (i == 0)
                {
                    if (j == 0)
                    {
                        label = label + 1;
                        linked.push_back(0);
                        imgcopy[i].push_back(label);
                    }
                    if (j > 0)
                    {
                        if (imgcopy[i][j - 1] != 0)
                        {
                            imgcopy[i].push_back(imgcopy[i][j - 1]);
                        }
                        else
                        {
                            label = label + 1;
                            linked.push_back(0);
                            imgcopy[i].push_back(label);
                        }

                    }
                }
                if ((j == 0)&&(i!=0))
                {
                    if (imgcopy[i - 1][j] != 0)
                    {
                        imgcopy[i].push_back(imgcopy[i - 1][j]);
                    }
                    else
                    {
                        label = label + 1;
                        linked.push_back(0);
                        imgcopy[i].push_back(label);
                    }
                }
                if ((i > 0) && (j > 0) && (i < img.rows - 1))
                {
                    B = imgcopy[i][j - 1];
                    C = imgcopy[i - 1][j];
                    D = imgcopy[i - 1][j - 1];
                    E = imgcopy[i - 1][j + 1];
                    if ((B == 0) && (C == 0) && (D == 0) && (E == 0))
                    {
                        label = label + 1;
                        linked.push_back(0);
                        imgcopy[i].push_back(label);
                    }
                    else
                    {
                        bool flag = false;
                        int min_num_comps;
                        if (B != 0)
                        {
                            if (flag == false)
                            {
                                flag = true;
                                min_num_comps = B;
                            }
                            else
                                if (B < min_num_comps)
                                    min_num_comps = B;
                        }
                        if (C != 0)
                        {
                            if (flag == false)
                            {
                                flag = true;
                                min_num_comps = C;
                            }
                            else
                                if (C < min_num_comps)
                                    min_num_comps = C;
                        }
                        if (D != 0)
                        {
                            if (flag == false)
                            {
                                flag = true;
                                min_num_comps = D;
                            }
                            else
                                if (D < min_num_comps)
                                    min_num_comps = D;
                        }
                        if (E != 0)
                        {
                            if (flag == false)
                            {
                                flag = true;
                                min_num_comps = E;
                            }
                            else
                                if (E < min_num_comps)
                                    min_num_comps = E;
                        }
                        imgcopy[i].push_back(min_num_comps);
                        if ((B != 0)&&(B != min_num_comps))
                        {
                            linked[B-1] = min_num_comps;
                            union_(min_num_comps, B, linked);
                        }
                        if ((C != 0)&&(C != min_num_comps))
                        {
                            linked[C-1] = min_num_comps;
                            union_(min_num_comps, C, linked);
                        }
                        if ((D != 0)&&(D != min_num_comps))
                        {
                            linked[D-1] = min_num_comps;
                            union_(min_num_comps, D, linked);
                        }
                        if ((E != 0)&&(E != min_num_comps))
                        {
                            linked[E-1] = min_num_comps;
                            union_(min_num_comps, E, linked);
                        }
                    }
                }
                if ((i == img.rows - 1) && (j > 0))
                {
                    B = imgcopy[i][j - 1];
                    C = imgcopy[i - 1][j];
                    D = imgcopy[i - 1][j - 1];
                    if ((B == 0) && (C == 0) && (D == 0))
                    {
                        label = label + 1;
                        linked.push_back(0);
                        imgcopy[i].push_back(label);
                    }
                    else
                    {
                        bool flag = false;
                        int min_num_comps;
                        if (B != 0)
                        {
                            if (flag == false)
                            {
                                flag = true;
                                min_num_comps = B;
                            }
                            else
                                if (B < min_num_comps)
                                    min_num_comps = B;
                        }
                        if (C != 0)
                        {
                            if (flag == false)
                            {
                                flag = true;
                                min_num_comps = C;
                            }
                            else
                                if (C < min_num_comps)
                                    min_num_comps = C;
                        }
                        if (D != 0)
                        {
                            if (flag == false)
                            {
                                flag = true;
                                min_num_comps = D;
                            }
                            else
                                if (D < min_num_comps)
                                    min_num_comps = D;
                        }
                        imgcopy[i].push_back(min_num_comps);
                        if ((B != 0)&&(B != min_num_comps))
                        {
                            linked[B-1] = min_num_comps;
                            union_(min_num_comps, B, linked);
                        }
                        if ((C != 0)&&(C != min_num_comps))
                        {
                            linked[C-1] = min_num_comps;
                            union_(min_num_comps, C, linked);
                        }
                        if ((D != 0)&&(D != min_num_comps))
                        {
                            linked[D-1] = min_num_comps;
                            union_(min_num_comps, D, linked);
                        }
                    }
                }
            }
            }
    }
    for (int i = 0; i < imgcopy.size(); i++)
    {
        for (int j = 0; j < imgcopy[i].size(); j++)
        {
            if (img.at<uchar>(i, j) == 255)
                imgcopy[i][j] = find_(imgcopy[i][j], linked);
        }
    }
}

void create_set_of_components(std::vector<std::vector<int>>& comps, const std::vector<std::vector<int>>& imgcopy)
{
    std::vector<int> use;
    int p = 0;

    for (int i = 0; i < imgcopy.size(); i++)
       {
           for (int j = 0; j < imgcopy[i].size(); j++)
           {
               p = 0;
               if (imgcopy[i][j] != 0)
               {
                   for (int m = 0; m < comps.size(); m++)
                       if (comps[m][0] == imgcopy[i][j])
                       {
                           comps[m].push_back(i);
                           comps[m].push_back(j);
                           p = 1;
                       }
                   if (p == 0)
                   {
                       use.push_back(imgcopy[i][j]);
                       comps.push_back(use);
                       use.pop_back();
                       comps[0].push_back(i);
                       comps[0].push_back(j);
                   }
               }

           }
    }
}

std::vector<int> find_max_comp(const std::vector<std::vector<int>>& comps)
{
    int max_size_copms = comps[0].size();
    int max_size_copms_num = 0;
    for(int i = 0; i < comps.size();i++)
    {
        if (comps[i].size() > max_size_copms)
        {
            max_size_copms = comps[i].size();
            max_size_copms_num = i;
        }
    }
    return comps[max_size_copms_num];
}
