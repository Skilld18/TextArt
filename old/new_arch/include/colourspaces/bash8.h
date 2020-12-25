#ifndef LIBDRAW_BASH8_H
#define LIBDRAW_BASH8_H

#include "colourspace.h"
#include "utils.h"

class bash8 : public colourspace
{
public:
    bash8()
    {
        this->start = "\033[2J";
        this->pixelStart = "\e[";
        this->pixelEnd= "m";
        this->rowEnd = "\n";
        this->end = "\033[0;0f";
    }

    std::string convertPixel(cv::Vec3b pixel)
    {
        std::map<std::string, cv::Vec3b> colours;
        std::string closestColour;
        //Naive method to "match" colours
        colours["97"] = cv::Vec3b(  0,  0,  0); //white
//        colours["90"] = cv::Vec3b( 86, 86, 86); //dark grey
        colours["30"] = cv::Vec3b(255,255,255); //black
        colours["31"] = cv::Vec3b(255,  0,  0); //red
        colours["32"] = cv::Vec3b(  0,255,  0); //green
        colours["33"] = cv::Vec3b(255,255,  0); //yellow
        colours["34"] = cv::Vec3b(  0,  0,255); //blue
        colours["35"] = cv::Vec3b(255,  0,255); //magenta
        colours["36"] = cv::Vec3b(  0,255,255); //cyan
//        colours["37"] = cv::Vec3b(172,172,172); //light grey

        int diff = 9000;
        for (const auto& colour : colours)
        {
            //Not a mistake opencv orders pixel colours differently
            int tmp = abs(colour.second[0] - pixel[2]) +
                      abs(colour.second[1] - pixel[1]) +
                      abs(colour.second[2] - pixel[0]);
            if (tmp < diff)
            {
                diff = tmp;
                closestColour = colour.first;
            }
        }
        return pixelStart + closestColour + pixelEnd + Utils::blackRectangle;
    }

};

#endif //LIBDRAW_BASH8_H
