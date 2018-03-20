//
// Created by rdunk on 02/02/18.
//

#ifndef LIBDRAW_UTILS_H
#define LIBDRAW_UTILS_H

#include <string>
#include <sstream>
#include <sys/ioctl.h>
#include <unistd.h>


class Utils
{
public:
    constexpr static auto blackRectangle = "\u2588";
};

std::string toHex(int x, std::string pad, int size)
{
    // std::stringstream stream;
    // stream << setfill ('0') << setw(2)
    //        << std::hex << x;
    // return stream.str();
}

cv::Size getTerminalSize()
{
    struct winsize w;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
    return cv::Size(w.ws_col, w.ws_row);
}

#endif //LIBDRAW_UTILS_H
