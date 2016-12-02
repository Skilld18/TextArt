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
int frame = -1;


using namespace ::cv;
using namespace ::std;

//TODO:: Find a way to exit without user input
//TODO:: Get data on render time
int main(int argc, char *argv[]) {

    if (argc < 2) {
        cout << "This program requires a image, video, document or textfile as an argument" << endl;
        return 1;
    }



    //Setup Screen
    int termWidth, termHeight;
    getTerminalSize(termWidth, termHeight);
    system("setterm -cursor off");
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
            frame++;
            string cmd = "convert " + filename + " tmp.png";
            system(cmd.c_str());
            char buffer[10];
            snprintf(buffer, 10, "%d", frame);
            img = imread("tmp-" + (string) buffer + ".png", CV_LOAD_IMAGE_COLOR);
        }
        else if (ft == IMG) {
            frame = 0;
            img = imread(filename, CV_LOAD_IMAGE_COLOR);
        }
        else if (ft == TXT) {
            printFile(filename);
        }
        else {
            cout << "That's not a valid file!" << endl;
            return 1;
        }
        resize(img, dst, Size(termWidth, termHeight));
        cout << matToPixels(dst);

        if(writeToFile){
            char buffer[10];
            snprintf(buffer, 10, "%d", frame);
            string outFileName = filename + "-textart" + buffer;
            ofstream outFile;
            outFile.open(outFileName.c_str());
            outFile << matToPixels(dst);
        }


        //TODO:: Deal with multiple pages
        //TODO:: Paging textfiles
        if (interactive) {
            char input = getch();
            if (input == ' '){
                frame++;
            }
            else if(input=='j'){
                panY += imgHeight;
            }
            else if(input=='k') {
                panY -= imgHeight;
            }
            else if(input=='h'){
                panX-= imgWidth;
            }
            else if(input=='l'){
                panY-= imgWidth;
            }
            else if(input=='-'){
                zoom_ratio /= 1.5;
            }
            else if(input=='+'){
                zoom_ratio *= 1.5;
            }
        }
    } while (ft == VID || interactive);

    return 0;
}


