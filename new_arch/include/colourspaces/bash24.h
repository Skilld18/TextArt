#ifndef LIBDRAW_BASH24_H
#define LIBDRAW_BASH24_H

#include "colourspace.h"
#include "utils.h"

class bash24 : public colourspace
{
public:
    bash24()
    {
        this->start = "\033[2J";
        this->pixelStart = "\e[49m\x1b[38;2";
        this->channelStart = ";";
        this->pixelEnd = "m";
        this->rowEnd = "\n";
        this->end = "\033[0;0f";
    }

    std::string convertPixel(cv::Vec3b pixel)
    {
        std::stringstream s;
        s << pixelStart
          << channelStart << (int)pixel[2]
          << channelStart << (int)pixel[1]
          << channelStart << (int)pixel[0]
          << pixelEnd << Utils::blackRectangle;
        return s.str();
    }

};

#endif //LIBDRAW_BASH24_H
