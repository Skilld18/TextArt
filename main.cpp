#include <iostream>
#include <fstream>
#include <opencv2/opencv.hpp>
#include "image.h"
#include "utils.h"
#include <string>
#include <sstream>



//TODO:: Attempt to compensate for font width vs height
//TODO:: Add a preserve aspect ratio

//Scaling and transform variables
float fontHeight = 1.0;
float fontWidth = 0.6;
float zoom_ratio = 1.0;
int panX = 0;
int panY = 0;
int imgHeight = 100;
int imgWidth = 100;
int frame = 0;


using namespace ::cv;
using namespace ::std;


//Example for passing in a function that can use different strings in the picture
string charAtPos(int i, int j) {
    if (i < 5 && j < 5) {
        return "t";
    }
    return "x";
}

//TODO:: Get data on render time
int main(int argc, char *argv[]) {

    if (argc < 2) {
        cout << "This program requires a image, video, document or textfile as an argument" << endl;
        return 1;
    }



    //Setup Screen
    int termWidth, termHeight;
    getTerminalSize(termWidth, termHeight);
//    system("setterm -cursor off");
    //    system ("/bin/stty cooked");
    //    system("export PS1=\"\"");

    //setup vars
    Mat img;
    Mat dst;
    VideoCapture capture;

    //Default Settings
    FileType ft = NONE;
    bool preserveAspectRatio = false;
    bool interactive = false;
    bool writeToFile = false;
    String filename = setOptions(argc, argv, &preserveAspectRatio, &interactive, &writeToFile, &ft);

    if (ft == VID) {
        capture.open(filename);
    }

    do {
        //Initializing files so they will work with the program
        //TODO:: Refine this
        //TODO:: Video Jumps??
        //TODO:: Load into buffer
        if (ft == VID) {
            bool success = capture.read(img);
            if (!success) {
                return 0;
            }
            capture >> img;
            frame++;
        }
            //This will convert doc files to tmp-0.png tmp-1.png etc.
        else if (ft == DOC) {
            string cmd = "convert " + filename + " tmp.png";
            system(cmd.c_str());
            char buffer[10];
            snprintf(buffer, 10, "%d", frame);
            img = imread("tmp-" + (string) buffer + ".png", CV_LOAD_IMAGE_COLOR);
            frame++;
        }
        else if (ft == IMG) {
            img = imread(filename, CV_LOAD_IMAGE_COLOR);
        }
        else if (ft == TXT) {
            printFile(filename, frame * termHeight, (frame + 1) * termHeight);
        }
        else {
            cout << "That's not a valid file!" << endl;
            return 1;
        }
        if (ft != TXT) {
            //TODO:: Get ROI rectangle
            resize(img, dst, Size(termWidth, termHeight));
            cout << matToPixels(dst, charAtPos);
            if (writeToFile) {
                char buffer[10];
                snprintf(buffer, 10, "%d", frame);
                string outFileName = filename + "-textart" + buffer;
                ofstream outFile;
                outFile.open(outFileName.c_str());
                outFile << matToPixels(dst);
            }
        }


        //TODO:: Deal with multiple pages
        if (interactive) {
            userInput(&frame, &panX, &panY, &zoom_ratio, imgWidth, imgHeight);
        }

    } while (ft == VID || interactive);

    return 0;
}


