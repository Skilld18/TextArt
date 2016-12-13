#include "utils.h"

#include <iostream>
#include <fstream>
#include <sys/ioctl.h>
#include <sys/stat.h>
#include <unistd.h>
#include <termios.h>


int isDirectory(string filename) {
    struct stat statbuf;
    if (stat(filename.c_str(), &statbuf) != 0)
        return 0;
    return S_ISDIR(statbuf.st_mode);
}

bool fileExists(const std::string &name) {
    struct stat buffer;
    return (stat(name.c_str(), &buffer) == 0);
}

string getFileExt(const string &s) {
    size_t i = s.rfind('.', s.length());
    if (i != string::npos) {
        return (s.substr(i, s.length() - i));
    }
    return ("");
}

bool contains(string s1, const string s2[]) {
    for (int i = 0; i < s2->size(); i++) {
        if (s2[0].find(s1) != string::npos) {
            return true;
        }
    }
    return false;
}

//I've yet to find a good way to do this so ...
FileType getFileType(string filename) {
    if (contains(getFileExt(filename), image_types))
        return IMG;
    else if (contains(getFileExt(filename), vid_types))
        return VID;
    else if (contains(getFileExt(filename), doc_types))
        return DOC;
    else if (isDirectory(filename))
        return DIR;
    else if (fileExists(filename))
        return TXT;
    return NONE;
}


void getTerminalSize(int &termWidth, int &termHeight) {
    struct winsize size;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &size);
    //Some terminals return 0 for this so for now set a lower bound
    termWidth = max((int)size.ws_col, 80);
    termHeight = max((int)size.ws_row, 24);
}

//TODO:: Bounds checking
void printFile(string filename, int start, int end) {
    string line;
    int i = 0;
    ifstream myfile(filename.c_str());
    if (myfile.is_open()) {
        while (getline(myfile, line)) {
            if (i>=start && i<end) {
                cout << line << '\n';
            }
            i++;
        }
        myfile.close();
    }
}

char getch(){
    char buf=0;
    struct termios old={0};
    fflush(stdout);
    if(tcgetattr(0, &old)<0)
        perror("tcsetattr()");
    old.c_lflag&=~ICANON;
    old.c_lflag&=~ECHO;
    old.c_cc[VMIN]=1;
    old.c_cc[VTIME]=0;
    if(tcsetattr(0, TCSANOW, &old)<0)
        perror("tcsetattr ICANON");
    if(read(0,&buf,1)<0)
        perror("read()");
    old.c_lflag|=ICANON;
    old.c_lflag|=ECHO;
    if(tcsetattr(0, TCSADRAIN, &old)<0)
        perror ("tcsetattr ~ICANON");
    printf("%c\n",buf);
    return buf;
}

string setOptions(vector<string> args, bool *preserveAspectRatio, bool *interactive, bool *writeToFile, FileType *fileType){
    string filename = "";
    for(int i = 1;i<args.size();i++){
        //manual or automatic type logic, auto is still hacky
        if(args.at(i) == "-image"){
            *fileType = IMG;
        }
        else if(args.at(i)=="-video"){
            *fileType = IMG;
        }
        else if(args.at(i)=="-doc"){
            *fileType = DOC;
        }
        else if(args.at(i)=="-dir"){
            *fileType = DIR;
        }
        else if(args.at(i)=="-dir"){
            *fileType = TXT;
        }
        else if(args.at(i)[0] != '-'){
            filename = args.at(i);
            *fileType = getFileType(filename);
        }
        if(args.at(i)=="-par"){
            *preserveAspectRatio = true;
        }
        if(args.at(i)=="-i"){
            *interactive = true;
        }
        if(args.at(i)=="-write"){
            *writeToFile= true;
        }
    }
    return filename;
}

//TODO:: Add bounds checks
void userInput(int *frame, int *panX, int *panY, float *zoom_ratio, int imgWidth, int imgHeight){
    char input = getch();
    if (input == 'f'){
        *frame += 1;
    }
    else if (input == 'b'){
        *frame -= 1;
    }
    else if(input=='j'){
        *panY += imgHeight/2;
    }
    else if(input=='k') {
        *panY -= imgHeight/2;
    }
    else if(input=='h'){
        *panX-= imgWidth/2;
    }
    else if(input=='l'){
        *panY-= imgWidth/2;
    }
    else if(input=='-'){
        *zoom_ratio /= 1.5;
    }
    else if(input=='+'){
        *zoom_ratio *= 1.5;
    }
}

