#include <draw/draw.h>
#include <iostream>
#include <opencv4/opencv2/core.hpp>
#include <opencv4/opencv2/imgcodecs.hpp>
#include <opencv4/opencv2/imgproc.hpp>
#include <sys/ioctl.h>
#include <csignal>


std::string draw_pixel(const cv::Vec<unsigned char, 3>& vec)
{
    std::stringstream pixel;
    pixel << "\033[49m" << "\x1b[38;2;" << (int) vec[2] << ";" << (int) vec[1] << ";" << (int) vec[0] << "m" << "█" << "\x1b[0m";
    return pixel.str();
}

cv::Size getTerminalSize()
{
    struct winsize w{};
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
    return {w.ws_col, w.ws_row-1};
}


int draw(const std::string &filename)
{
    cv::Mat origin;
    origin = cv::imread(filename);
    cv::Mat img;
    resize(origin, img, {0,0}, 1, 0.43);
    origin = img;
    const auto s = getTerminalSize();
    float fx = origin.cols / s.width + 1;
    float fy = origin.rows / s.height + 1;
    float f = fx > fy ? fx : fy;
    int x = fx > fy ? s.width : origin.cols/f;
    int y = fx > fy ? origin.rows/f : s.height;
    resize(origin, img, {x,y});
    std::stringstream output;
    for (int i = 0; i < img.rows; i++)
    {
        for (int j = 0; j < img.cols; j++)
        {
            const auto pixel = img.at<cv::Vec3b>(i, j);
            output << draw_pixel(pixel);
        }
        output << "\n";
    }
    std::cout << output.str();
    return 0;
}