#include "../include/draw.h"
#include "opencv2/opencv.hpp"
int main(int argc, char ** argv)
{

    cv::Mat mat = cv::imread("../sunflowers.jpg");
    cv::Mat sizedMat;
    cv::resize(mat, sizedMat, cv::Size(20,20));

    draw(sizedMat);

    return 0;
}