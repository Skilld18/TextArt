#include "../include/draw.h"
#include "opencv2/opencv.hpp"
#include <getopt.h>

int main(int argc, char **argv)
{

    char c;
    bool aflag, bflag;
    std::string cvalue;
    while (optind < argc)
    {
        if ((c = getopt(argc, argv, "hil:pt:vw:")) != -1)
        {
            switch (c)
            {
                case 'h':
                {
                    std::cout << "print the help screen" << std::endl;
                    break;
                }
                case 'v':
                {
                    std::cout << "version info" << std::endl;
                    break;
                }
                default:
                    break;
            }
        }
        else
        {
            if(argv[optind])
            {
                std::cout << "Filename "  << argv[optind] << std::endl;
            }
            optind++;  // Skip to the next argument
        }
    }

    cv::Mat mat = cv::imread("../sunflowers.jpg");
    cv::Mat sizedMat;
    cv::resize(mat, sizedMat, cv::Size(20, 20));

    draw(sizedMat);

    return 0;
}