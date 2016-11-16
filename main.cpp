#include <iostream>
#include <fstream>

#include <opencv2/opencv.hpp>

#include "image.h"
#include "utils.h"

#include <dirent.h>

float fontHeight = 1.0;
float fontWidth = 0.6;


using namespace ::cv;
using namespace ::std;
int listdir(const char *path) {
    struct dirent *entry;
    DIR *dp;

    dp = opendir(path);
    if (dp == NULL) {
        perror("opendir");
        return -1;
    }

    while((entry = readdir(dp)))
        puts(entry->d_name);

    closedir(dp);
    return 0;
}


int main(int argc, char* argv[]) {

    //Setup
    system("setterm -cursor off");
    int termWidth;
    int termHeight;
    getTerminalSize(termWidth,termHeight);
    if(argc<2){
        cout << "This program requires a image, video, document or textfile as an argument" << endl;
        return 1;
    }

    string filename = argv[1];
    FileType ft = getFileType(filename);
    //Manually setting type
    if(argc >=3){
        if (strcmp("-i", argv[2])==0)
            ft = IMG;
        else if (strcmp("-v", argv[2])==0)
            ft = VID;
        else if (strcmp("-d", argv[2])==0)
            ft = DOC;
        else if (strcmp("-f", argv[2])==0)
            ft = DIRE;
        else if (strcmp("-t", argv[2])==0)
            ft = TXT;
    }

    if (ft == IMG){
        cout << matToPixels(imread(filename, CV_LOAD_IMAGE_COLOR));
    }
    //TODO:: Refine this
    else if (ft == VID){
        VideoCapture capture;
        capture.open(filename);
        Mat img;
        Mat dst;
        for (;;) {
            capture >> img;
            resize(img, dst, Size(termWidth, termHeight));
            if (img.empty())
                break;
            cout << matToPixels(dst);
        }
    }
    //TODO:: Conversions
        //TODO:: fix redundant code
    else if (ft == DOC){
        string cmd = "convert " + filename + " tmp.png";
        system(cmd.c_str());
        Mat img = imread("tmp-2.png", CV_LOAD_IMAGE_COLOR);
        Mat dst;
        resize(img, dst, Size(termWidth, termHeight));
        cout << matToPixels(dst);
    }
    //TODO:: Recursives
    else if (ft == DIRE){
        int counter = 0;
        while (++counter <= argc) {
            printf("\nListing %s...\n", argv[counter-1]);
            listdir(argv[counter-1]);
        }
    }
    else if (ft == TXT){
        printFile(filename);
    }
    else{
        cout << "That's not a valid file!" << endl;
    }
    //set everything back
//    system("setterm -cursor on");
    return 0;
}
