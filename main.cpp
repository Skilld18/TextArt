#include <iostream>
#include <fstream>
#include <opencv2/opencv.hpp>
#include "image.h"
#include "utils.h"


//TODO:: Attempt to compensate for font width vs height
float fontHeight = 1.0;
float fontWidth = 0.6;


float zoom_ratio = 1.0;
int panX = 0;
int panY = 0;
int frame = 0;
bool play = false;


using namespace ::cv;
using namespace ::std;

//TODO:: Find a way to exit without user input
//TODO:: Get data on render time
int main(int argc, char *argv[]) {

    if (argc < 2) {
        cout << "This program requires a image, video, document or textfile as an argument" << endl;
        return 1;
    }

    int termWidth, termHeight;
    getTerminalSize(termWidth, termHeight);
    string filename = argv[1];

    //This will always be a guess so allow the user to manually set filetype
    FileType ft = getFileType(filename);
    bool skip = false;
    if (argc >= 3) {
        if (strcmp("-i", argv[2]) == 0)
            ft = IMG;
        else if (strcmp("-v", argv[2]) == 0)
            ft = VID;
        else if (strcmp("-d", argv[2]) == 0)
            ft = DOC;
        else if (strcmp("-f", argv[2]) == 0)
            ft = DIR;
        else if (strcmp("-t", argv[2]) == 0)
            ft = TXT;
    }

    system("setterm -cursor off");
//    system ("/bin/stty cooked");
//    system("export PS1=\"\"");
    Mat img;
    Mat dst;

    //Initializing files so they will work with the program
    //TODO:: Refine this
    //TODO:: Video Jumps??
    //TODO:: Load into buffer
    //TODO:: infinite loop video
    if (ft == VID) {
        VideoCapture capture;
        capture.open(filename);
        for (; ;) {
            capture >> img;
            resize(img, dst, Size(termWidth, termHeight));
            cout << matToPixels(dst);
        }
    }
    //This will convert doc files to tmp-0.png tmp-1.png etc.
        //TODO:: Deal with multiple pages
    else if (ft == DOC) {
        string cmd = "convert " + filename + " tmp.png";
        system(cmd.c_str());
        char buffer[10];
        snprintf(buffer, 10, "%d", frame);
        img = imread("tmp-" + (string) buffer + ".png", CV_LOAD_IMAGE_COLOR);
    }

    else if (ft == IMG) {
        img = imread(filename, CV_LOAD_IMAGE_COLOR);
    }
    //TODO:: This could use a scrolling method like more or less
    else if (ft == TXT) {
        printFile(filename);
    }
    else {
        cout << "That's not a valid file!" << endl;
    }
    resize(img, dst, Size(termWidth, termHeight));
    cout << matToPixels(dst);

    return 0;
}


