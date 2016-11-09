#include <iostream>
#include <fstream>


#include <opencv2/opencv.hpp>

#include "image.h"
#include "utils.h"


float fontHeight = 1.0;
float fontWidth = 0.6;


using namespace ::cv;
using namespace ::std;




int main() {
    //Setup
    system("setterm -cursor off");
    int termWidth;
    int termHeight;
    getTerminalSize(termWidth,termHeight);

    string filename = "img.jpg";
    FileType ft = getFileType(filename);
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
            //BUG here
            resize(img, dst, Size(termWidth, termHeight-1));
            if (img.empty())
                break;
            cout << matToPixels(dst);
        }
    }
        //TODO:: Conversions
    else if (ft == DOC){}
        //TODO:: Recursives
    else if (ft == DIR){}
    else if (ft == TXT){
        string line;
        ifstream myfile(filename.c_str());
        if (myfile.is_open())
        {
            while ( getline (myfile,line) )
            {
                cout << line << '\n';
            }
            myfile.close();
        }
    }
    else{
        cout << "That's not a valid file!" << endl;
    }
    //set everything back
    system("setterm -cursor on");
    return 0;
}
