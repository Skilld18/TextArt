//
// Created by rdunk on 02/02/18.
//

#ifndef LIBDRAW_UTILS_H
#define LIBDRAW_UTILS_H

#include <string>
#include <sstream>
#include <sys/ioctl.h>
#include <unistd.h>
#include "opencv2/opencv.hpp"


class Utils
{
public:
    constexpr static auto blackRectangle = "\u2588";
};

std::string toHex(int x, std::string pad, int size);
cv::Size getTerminalSize();

#endif //LIBDRAW_UTILS_H
