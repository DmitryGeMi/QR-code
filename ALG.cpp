void ccl_algorithm(std::vector<std::vector<int>>& imgcopy, const cv::Mat &img)
{
std::vector<int> linked;
int label = 0, B = 0, C = 0, D = 0;

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
                if ((i > 0) && (j > 0))
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
                    if ((B != 0) && (C == 0) && (D == 0))
                    {
                        imgcopy[i].push_back(B);
                    }
                    if ((B == 0) && (C != 0) && (D == 0))
                    {
                        imgcopy[i].push_back(C);
                    }
                    if ((B == 0) && (C == 0) && (D != 0))
                    {
                        imgcopy[i].push_back(D);
                    }
                    if ((B != 0) && (C != 0) && (D == 0))
                    {
                        if (B == C)
                        {
                            imgcopy[i].push_back(B);
                        }
                        else
                        {
                            if (B > C)
                            {
                                linked[B-1] = C;
                                imgcopy[i].push_back(C);
                                union_(C, B, linked);
                            }
                            else
                            {
                                linked[C-1] = B;
                                imgcopy[i].push_back(B);
                                union_(B, C, linked);
                            }
                        }
                    }
                    if ((B != 0) && (C == 0) && (D != 0))
                    {
                        if (B == D)
                        {
                            imgcopy[i].push_back(B);
                        }
                        else
                        {
                            if (B > D)
                            {
                                linked[B-1] = D;
                                imgcopy[i].push_back(D);
                                union_(D, B, linked);
                            }
                            else
                            {
                                linked[D-1] = B;
                                imgcopy[i].push_back(B);
                                union_(B, D, linked);
                            }
                        }
                    }
                    if ((B == 0) && (C != 0) && (D != 0))
                    {
                        if (D == C)
                        {
                            imgcopy[i].push_back(D);

                        }
                        else
                        {
                            if (D > C)
                            {
                                linked[D-1] = C;
                                imgcopy[i].push_back(C);
                                union_(C, D, linked);
                            }
                            else
                            {
                                linked[C-1] = D;
                                imgcopy[i].push_back(D);
                                union_(D, C, linked);
                            }
                        }
                    }
                    if ((B != 0) && (C != 0) && (D != 0))
                    {
                        if ((B == C) && (C == D))
                        {
                            imgcopy[i].push_back(D);

                        }
                        else
                        {
                            if (B > C)
                            {
                                linked[B-1] = C;
                                union_(C, B, linked);
                                if (D > C)
                                {
                                    linked[D-1] = C;
                                    imgcopy[i].push_back(C);
                                    union_(C, D, linked);
                                }
                                else
                                {
                                    linked[C-1] = D;
                                    imgcopy[i].push_back(D);
                                    union_(D, C, linked);
                                }
                            }
                            else
                            {
                                linked[C-1] = B;
                                union_(B, C, linked);
                                if (D > B)
                                {
                                    linked[D-1] = B;
                                    imgcopy[i].push_back(B);
                                    union_(B, D, linked);
                                }
                                else
                                {
                                    linked[B-1] = D;
                                    imgcopy[i].push_back(D);
                                    union_(D, B, linked);
                                }
                            }
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