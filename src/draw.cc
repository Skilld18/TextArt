#include <draw/draw.h>
#include <iostream>
#include <opencv4/opencv2/core.hpp>
#include <opencv4/opencv2/imgcodecs.hpp>
#include <opencv4/opencv2/imgproc.hpp>

int draw(Options options, std::string Filename)
{
    if (Filename.empty())
    {
        return 3;
    }
    if (!options.is_initialized())
    {
        return 4;
    }
    cv::Mat img;
    img = cv::imread(Filename);
    resize(img, img, cv::Size(static_cast<int>(options.get_width()), static_cast<int>(options.get_height())));

    for (int i=0; i<img.rows; i++)
    {
        for(int j=0; j<img.cols; j++) 
        {
            const auto pixel = img.at<cv::Vec3b>(i,j);
            if (pixel[0] + pixel[1] + pixel[2] < 430)
            {
               std::cout << 'c';
            }
            else
            {
                std::cout << ' ';
            }
        }
        std::cout << "\n";
    }

    return 0;
}