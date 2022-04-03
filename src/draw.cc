#include <draw/draw.h>
#include <iostream>
#include <opencv4/opencv2/core.hpp>
#include <opencv4/opencv2/imgcodecs.hpp>
#include <opencv4/opencv2/imgproc.hpp>

std::string draw_pixel(const std::string &glyph)
{
    return glyph;
}

std::string draw_newline()
{
    return "\n";
}

int draw(Options &options, const std::string &filename)
{
    if (filename.empty()) {
        return 3;
    }

    if (!options.is_initialized()) {
        return 4;
    }

    cv::Mat origin;
    origin = cv::imread(filename);
    cv::Mat img;
    const auto s = cv::Size(30, 30);
    resize(origin, img, s);

    for (int i = 0; i < img.rows; i++)
    {
        for (int j = 0; j < img.cols; j++)
        {
            const auto pixel = img.at<cv::Vec3b>(i, j);
            if (pixel[0] + pixel[1] + pixel[2] < 430)
            {
                std::cout << draw_pixel("c");
            }
            else 
            {
                std::cout << draw_pixel(" ");
            }
        }
        std::cout << draw_newline();
    }

    return 0;
}