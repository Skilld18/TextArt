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

cv::Size getRescaledSize(cv::Size terminal, cv::Size image)
{
    float scale_width = image.width / terminal.width + 1;
    float scale_height = image.height / terminal.height + 1;
    float scaling_factor = scale_width > scale_height ? scale_width : scale_height;
    int width = scale_width > scale_height ? terminal.width : image.width/scaling_factor;
    int height = scale_width > scale_height ? image.height/scaling_factor : terminal.height;
    return {width, height};
}


int draw(const std::string &filename)
{
    cv::Mat origin;
    origin = cv::imread(filename);
    cv::Mat img;
    resize(origin, img, {0,0}, 1, 0.43);
    origin = img;
    const auto terminalSize = getTerminalSize();
    const cv::Size imageSize = {origin.cols, origin.rows};
    resize(origin, img, getRescaledSize(terminalSize, imageSize));
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