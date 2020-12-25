#include "draw.h"
#include "opencv2/opencv.hpp"
#include <numeric>
#include <options.h>
#include "colourspace.h"
#include "colourspaces/bash24.h"
#include "colourspaces/bash8.h"
#include "colourspaces/html.h"
#include "utils.h"


void draw(cv::Mat mat)
{
    colourspace *cs = new bash8();
    std::string output = cs->start;
    for (int i = 0;i<mat.rows;i++)
    {
        output += cs->rowStart;
        for (int j = 0;j<mat.cols;j++)
        {
            //char rules
            output += cs->convertPixel(mat.at<cv::Vec3b>(i, j));
        }
        output += cs->rowEnd;
    }
    output += cs->end;
    std:: cout << output;
}
