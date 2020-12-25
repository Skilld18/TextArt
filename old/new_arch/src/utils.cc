#include "utils.h"

std::string toHex(int x, std::string pad, int size)
{
    // std::stringstream stream;
    // stream << setfill ('0') << setw(2)
    //        << std::hex << x;
    // return stream.str();
    return "";
}

cv::Size getTerminalSize()
{
    struct winsize w;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
    return cv::Size(w.ws_col, w.ws_row-1);
}

