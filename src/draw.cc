#include <draw/draw.h>
#include <iostream>
#include <opencv4/opencv2/core.hpp>
#include <opencv4/opencv2/imgcodecs.hpp>
#include <opencv4/opencv2/imgproc.hpp>

std::string draw_pixel(const cv::Vec<unsigned char, 3> vec, const std::string &glyph, const Options::ColourSpace cs)
{
    std::stringstream pixel;
    if (cs == Options::BASH24)
    {
        pixel << "\033[49m" << "\x1b[38;2;" << (int) vec[2] << ";" << (int) vec[1]
              << ";" << (int) vec[0] << "m" << glyph << "\x1b[0m";
    }
    else
    {
        return "f";
    }
    return pixel.str();
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
            std::cout << draw_pixel(pixel, get_glyph(), get_colourspace());
        }
        std::cout << draw_newline();
    }

    return 0;
}

std::string get_glyph()
{
    return "\u2588";
}

Options::ColourSpace get_colourspace()
{
    return Options::ColourSpace::BASH24;
}