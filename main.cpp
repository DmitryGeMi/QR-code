#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>
#include <string>
#include <algorithm>
#include <vector>

#include "add.h"
#include "makeWhite_outside_rect.h"

using namespace cv;
using namespace std;

struct grad
{
    double i;
    double j;
};


point intersection(point a, point b, point c, point d)
{
    point p;
    double a1, a2, b1, b2, c1, c2, det;
    a1 = a.j - b.j;
    b1 = b.i - a.i;
    c1 = a.i * b.j - b.i * a.j;
    a2 = c.j - d.j;
    b2 = d.i - c.i;
    c2 = c.i * d.j - d.i * c.j;
    det = a1 * b2 - a2 * b1;
    p.i = (b1 * c2 - b2 * c1) / det;
    p.j = (a2 * c1 - a1 * c2) / det;
    return p;
}
double ang(point a, point b, point c)
{
    return ((c.i - b.i)*(b.i - a.i) + (c.j - b.j)*(b.j - a.j)) / (sqrt(dist(a, b))*(sqrt(dist(c, b))));
}


vector <vector < grad>> gradient(vector <vector < double>> mat, int a, int b)
{
    vector <vector < grad>> grad(a);
    int i, j;
    double maxgrad = 0;
    for (i = 0; i < a; i++)
    {
        grad[i].resize(b);
    }
    for (i = 1; i < a - 1; i++)
    {
        for (j = 1; j < b - 1; j++)
        {
            grad[i][j].i = mat[i+1][j-1] + 2* mat[i+1][j] + mat[i+1][j+1] - mat[i-1][j-1] - 2*mat[i-1][j] - mat[i-1][j+1];
            grad[i][j].j = mat[i-1][j+1] + 2*mat[i][j+1] + mat[i+1][j+1] - mat[i-1][j-1] - 2*mat[i][j-1] - mat[i+1][j-1];
            //cout << "i " << i << " j " << j << " " << grad[i][j] << endl;
            if (sqrt(grad[i][j].i*grad[i][j].i + grad[i][j].j*grad[i][j].j) > maxgrad)
                maxgrad = sqrt(grad[i][j].i*grad[i][j].i + grad[i][j].j*grad[i][j].j);
        }
    }
    for (i = 0; i < a; i++)
    {
        for (j = 0; j < b; j++)
        {
            grad[i][j].i = grad[i][j].i / maxgrad;
            grad[i][j].j = grad[i][j].j / maxgrad;
            if (sqrt(grad[i][j].i*grad[i][j].i + grad[i][j].j*grad[i][j].j) < 0.3)
            {
                grad[i][j].i = 0;
                grad[i][j].j = 0;
            }
        }
    }
    return grad;
}

void window(vector <vector < grad>> mat, int a, int b, Mat *img,int &lft,int &rt,int &up,int &down)
{
    vector <vector < bool>> wind(a);
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
            for (m = max(0, i - a / obl); m < min(a - 1, i + a / obl); m++)
            {
                for (k = max(0, j - b / obl); k < min(b - 1, j + b / obl); k++)
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
void boundary_point(vector <point> *pnt, Mat *img)
{
    point point;
    bool flg = false;
    int i, j, m;
    for (i = 0; i < img->rows; i++)
        for (j = 0; j < img->cols; j++)
        {
            if ((img->at<Vec3b>(i, j)[0] < 60) && (img->at<Vec3b>(i, j)[1] < 60) && (img->at<Vec3b>(i, j)[2] < 60))
            {
                point.i = i;
                point.j = j;
                pnt->push_back(point);
                break;
            }
        }
    for (j = img->cols - 1; j > 0; j--)
        for (i = 0; i < img->rows; i++)
        {
            if ((img->at<Vec3b>(i, j)[0] < 60) && (img->at<Vec3b>(i, j)[1] < 60) && (img->at<Vec3b>(i, j)[2] < 60))
            {
                for (m = 0; m < pnt->size(); m++)
                {
                    if ((pnt->at(m).i == i) && (pnt->at(m).j == j))
                    {
                        flg = true;
                    }
                }
                if (flg == false)
                {
                    point.i = i;
                    point.j = j;
                    pnt->push_back(point);
                }
                flg = false;
                break;
            }
        }
    for (j = 0; j < img->cols; j++)
        for (i = img->rows - 1; i > 0; i--)
        {
            if ((img->at<Vec3b>(i, j)[0] < 60) && (img->at<Vec3b>(i, j)[1] < 60) && (img->at<Vec3b>(i, j)[2] < 60))
            {
                for (m = 0; m < pnt->size(); m++)
                {
                    if ((pnt->at(m).i == i) && (pnt->at(m).j == j))
                    {
                        flg = true;
                    }
                }
                if (flg == false)
                {
                    point.i = i;
                    point.j = j;
                    pnt->push_back(point);
                }
                flg = false;
                break;
            }
        }
    for (i = img->rows - 1; i > 0; i--)
        for (j = img->cols - 1; j > 0; j--)
        {
            if ((img->at<Vec3b>(i, j)[0] < 60) && (img->at<Vec3b>(i, j)[1] < 60) && (img->at<Vec3b>(i, j)[2] < 60))
            {
                for (m = 0; m < pnt->size(); m++)
                {
                    if ((pnt->at(m).i == i) && (pnt->at(m).j == j))
                    {
                        flg = true;
                    }
                }
                if (flg == false)
                {
                    point.i = i;
                    point.j = j;
                    pnt->push_back(point);
                }
                flg = false;
                break;
            }
        }
}
void simplifying_hall(vector <point> *hull)
{
    int m, j;
    double e = 0.995;
    for (m = 0; m < hull->size(); m++)
    {
        if (ang(hull->at(m % hull->size()), hull->at((m + 1) % hull->size()), hull->at((m + 2) % hull->size())) > e)
        {
            j = (m + 1) % hull->size();
            hull->erase(hull->begin() + j);
        }
    }
}
void add_point_pntinside(point *pntinside, point point1, point point2)
{
    pntinside[6].i = point1.i;
    pntinside[6].j = point1.j;
    pntinside[7].i = point2.i;
    pntinside[7].j = point2.j;
}
void move_point_3_4(point *pntinside)
{
    pntinside[0].i = pntinside[2].i;
    pntinside[0].j = pntinside[2].j;
    pntinside[1].i = pntinside[3].i;
    pntinside[1].j = pntinside[3].j;
}
void move_point_5_6(point *pntinside)
{
    pntinside[2].i = pntinside[4].i;
    pntinside[2].j = pntinside[4].j;
    pntinside[3].i = pntinside[5].i;
    pntinside[3].j = pntinside[5].j;
}
void move_point_7_8(point *pntinside)
{
    pntinside[4].i = pntinside[6].i;
    pntinside[4].j = pntinside[6].j;
    pntinside[5].i = pntinside[7].i;
    pntinside[5].j = pntinside[7].j;
}
void finding_corner_points(vector <point> *hull, point *pntinside)
{
    int k = 0, l1, l2, l3, l4, m;
    l1 = dist(hull->at(0), hull->at(1));
    l2 = dist(hull->at(1), hull->at(2));
    l3 = dist(hull->at(2), hull->at(3));
    if (hull->size() == 4)
        l4 = dist(hull->at(3), hull->at(0));
    else
        l4 = dist(hull->at(3), hull->at(4));
    for (m = 0; m < 8; m = m + 2)
    {
        pntinside[m].i = hull->at(k % hull->size()).i;
        pntinside[m].j = hull->at(k % hull->size()).j;
        pntinside[m + 1].i = hull->at((k + 1) % hull->size()).i;
        pntinside[m + 1].j = hull->at((k + 1) % hull->size()).j;
        k++;
    }
    bool flg = true;
    for (m = 4; m < hull->size(); m++)
    {
        if ((dist(hull->at(m), hull->at((m + 1) % hull->size())) >= l1) || (dist(hull->at(m), hull->at((m + 1) % hull->size())) >= l2) || (dist(hull->at(m), hull->at((m + 1) % hull->size())) >= l3) || (dist(hull->at(m), hull->at((m + 1) % hull->size())) >= l4))
        {
            flg = false;
            if ((l1 >= l4) && (l2 >= l4) && (l3 >= l4) && (flg == false))
            {
                l4 = dist(hull->at(m), hull->at((m + 1) % hull->size()));
                add_point_pntinside(pntinside, hull->at(m), hull->at((m + 1) % hull->size()));
                flg = true;
            }
            if ((l1 >= l3) && (l2 >= l3) && (l4 >= l3) && (flg == false))
            {
                l3 = l4;
                move_point_7_8(pntinside);
                l4 = dist(hull->at(m), hull->at((m + 1) % hull->size()));
                add_point_pntinside(pntinside, hull->at(m), hull->at((m + 1) % hull->size()));
                flg = true;
            }
            if ((l1 >= l2) && (l3 >= l2) && (l4 >= l2) && (flg == false))
            {
                l2 = l3;
                move_point_5_6(pntinside);
                l3 = l4;
                move_point_7_8(pntinside);
                l4 = dist(hull->at(m), hull->at((m + 1) % hull->size()));
                add_point_pntinside(pntinside, hull->at(m), hull->at((m + 1) % hull->size()));
                flg = true;
            }
            if ((l2 >= l1) && (l3 >= l1) && (l4 >= l1) && (flg == false))
            {
                l1 = l2;
                move_point_3_4(pntinside);
                l2 = l3;
                move_point_5_6(pntinside);
                l3 = l4;
                move_point_7_8(pntinside);
                l4 = dist(hull->at(m), hull->at((m + 1) % hull->size()));
                add_point_pntinside(pntinside, hull->at(m), hull->at((m + 1) % hull->size()));
                flg = true;
            }
        }
    }
}
void paint_angles(Mat *img, point *pntinside)
{
    point t;
    for (int m = 0; m < 8; m = m + 2)
    {
        t = intersection(pntinside[m % 8], pntinside[(m + 1) % 8], pntinside[(m + 2) % 8], pntinside[(m + 3) % 8]);
        circle(*img, Point(t.j, t.i), 1, Scalar(50, 100, 200));
    }
}
int  main(int argc, char* argv[])
{
    string path = "/home/user/QRcode/" + string(argv[1]);
    Mat img = imread(path);
    Mat imggrad(img.rows, img.cols, CV_8UC1);
    int i = 0, j = 0;
    int lft = img.cols - 1, rt = 0, up = img.rows - 1, down = 0;
    vector <point> pnt;
    vector <point> hull;
    point pntinside[8];
    vector <vector < double>> matrix(img.rows);
    for (i = 0; i < img.rows; i++)
    {
        matrix[i].resize(img.cols);
        for (j = 0; j < img.cols; j++)
        {
            matrix[i][j] = (img.at<Vec3b>(i, j)[0] + img.at<Vec3b>(i, j)[1] + img.at<Vec3b>(i, j)[2]) / 3;
        }
    }
    vector <vector < grad >> g(img.rows);
    for (i = 0; i < img.rows; i++)
        g[i].resize(img.cols);
    g = gradient(matrix, img.rows, img.cols);
    for (i = 0; i < imggrad.rows; i++)
        for (j = 0; j < imggrad.cols; j++)
            imggrad.at<uchar>(i, j) = sqrt(g[i][j].i*g[i][j].i + g[i][j].j*g[i][j].j) * 255;
    window(g, img.rows, img.cols, & img, lft, rt, up, down);
    makeWhite_outside_rect(& img, lft, rt, up, down);
    boundary_point(&pnt, &img);
    hull = convex_hull(pnt);
    simplifying_hall(&hull);
    finding_corner_points(&hull, pntinside);
    paint_angles(&img, pntinside);
    imwrite("res.jpg", img);
    imwrite("imggrad.jpg", imggrad);
    imshow("Gradient", imggrad);
    imshow("Display Window", img);
    waitKey(0);
    return 0;
}
