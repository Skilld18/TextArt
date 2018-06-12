#include "draw.h"
#include "opencv2/opencv.hpp"
#include <numeric>
#include "colourspace.h"
#include "colourspaces/bash24.h"
#include "colourspaces/html.h"
#include "utils.h"


void draw(char *filename) 
{
    auto old = cv::imread(filename);
    cv::Mat mat;
    resize(old,mat,getTerminalSize());


    auto cs = bash24();
//    auto cs = html();
    std::string output = cs.start;
    for (int i = 0;i<mat.rows;i++)
    {
        output += cs.rowStart;
        for (int j = 0;j<mat.cols;j++)
        {
            output += cs.convertPixel(mat.at<cv::Vec3b>(i, j));
        }
        output += cs.rowEnd;
    }
    output += cs.end;
    std:: cout << output;
}