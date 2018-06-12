//
// Created by rdunk on 01/02/18.
//

#ifndef LIBDRAW_COLOURSPACE_H
#define LIBDRAW_COLOURSPACE_H

#include <vector>
#include <ios>
#include "opencv2/opencv.hpp"

class colourspace
{
public:

    std::string start;
    std::string end;
    std::string rowStart;
    std::string rowEnd;
    std::string pixelStart;
    std::string pixelEnd;
    std::string channelStart;
    std::string channelEnd;
    int channelCount = 3;


    virtual std::string convertPixel(cv::Vec3b pixel) = 0;
};

#endif //LIBDRAW_COLOURSPACE_H
