#include <draw/draw.h>
#include <iostream>
#include <unistd.h>
#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>
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
    if (w.ws_col < 10)
    {
        w.ws_col = 80;
        std::cout << "Terminal width detection failed defaulting to "
            << w.ws_col << std::endl;
    }
    if (w.ws_row < 10)
    {
        w.ws_col = 24;
        std::cout << "Terminal height detection failed defaulting to "
            << w.ws_row <<  std::endl;
    }
    return {w.ws_col, w.ws_row-1};
}

cv::Size getRescaledSize(cv::Size terminal, cv::Size image)
{
    int scale_width = image.width / terminal.width + 1;
    int scale_height = image.height / terminal.height + 1;
    int scale = scale_width > scale_height ? scale_width : scale_height;
    int width = scale_width > scale_height ? terminal.width : image.width/scale;
    int height = scale_width > scale_height ? image.height/scale: terminal.height;
    return {width, height};
}


int draw(const std::string &filename)
{
    cv::Mat origin;
    origin = cv::imread(filename);
    cv::Mat img;
    try
    {
            resize(origin, img, {0,0}, 1, 0.43);
    }
    catch (std::exception &e)
    { 
        std::cout << e.what() << " bad image" << std::endl; 
        return 1;
    }
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
