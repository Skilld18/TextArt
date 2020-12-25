//
// Created by rdunk on 02/02/18.
//

#ifndef LIBDRAW_HTML_H
#define LIBDRAW_HTML_H

#include "colourspace.h"
#include "utils.h"

class html : public colourspace
{
public:
    html()
    {
        this->start = "<html>\n<meta http-equiv=\"Content-Type\" content=\"text/html; charset=UTF-8\">\n";
        this->pixelStart = "<h2 style=\"display: inline; color:#";
        this->pixelEnd = "\">";
        this->rowEnd = "<br>\n";
        this->end = "</html>";
    }

    std::string convertPixel(cv::Vec3b pixel)
    {
        std::stringstream s;
        s << pixelStart
            << toHex(pixel[2], "0", 2)
            << toHex(pixel[1], "0", 2)
            << toHex(pixel[0], "0", 2)
          << pixelEnd
          << Utils::blackRectangle
          << "</h2>";
        return s.str();
    }
};


#endif //LIBDRAW_HTML_H
