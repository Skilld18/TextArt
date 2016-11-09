#include <stdlib.h>
#include <ncurses.h>
#include <cv.h>
#include <sys/ioctl.h>
#include <iostream>
#include <unistd.h>
#include <opencv2/opencv.hpp>


enum colour {
    BW, ANSI, PALETTE, FULL
};

//Terminal variables
int termWidth = 200;
int termHeight = 60;
float fontHeight = 1.0;
float fontWidth = 0.6;
colour termColour;

void getConfig() {
    struct winsize size;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &size);
    termWidth = size.ws_col;
    termHeight = size.ws_row;
}

using namespace ::cv;
using namespace ::std;

void getPixelatPoint(Mat img, int x, int y) {
    Vec3b intensity = img.at<Vec3b>(y, x);
    uchar blue = intensity.val[0];
    uchar green = intensity.val[1];
    uchar red = intensity.val[2];
}


string writePixel(int red, int green, int blue, int glyph) {
    //TODO:: Cover all colours
    stringstream s;
    s << "\x1b[38;2;" << blue << ";" << green << ";" << red << "m█\x1b[0m";
    return s.str();
}


int main() {
    system("setterm -cursor off");
    string filename = "vid.mp4";
    getConfig();
    VideoCapture capture;
    capture.open(filename);
    Mat img;
    Mat dst;
    for (;;) {
        capture >> img;
        resize(img, dst, Size(termWidth, termHeight));
        if (img.empty())
            break;

        string t;
        for (int i = 0; i < termHeight - 1; i++) {
            for (int j = 0; j < termWidth; j++) {
                Vec3b intensity = dst.at<Vec3b>(i, j);
                t += writePixel(intensity[0], intensity[1], intensity[2], 10);
            }
            t += '\n';
        }
        t += "\033[0;0f";
        cout << t;
    }

    system("setterm -cursor on");
    return 0;
}
