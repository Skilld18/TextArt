#include "utils.h"

#include <iostream>
#include <fstream>
#include <sys/ioctl.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string>
#include <string.h>
#include <termios.h>
#include <stdio.h>




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
        return (s.substr(i + 1, s.length() - i));
    }
    return ("");
}

bool contains(string s1, const string s2[]) {
    for (int i = 0; i < sizeof(s2) / sizeof(s2[0]); i++) {
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
    termWidth = size.ws_col;
    termHeight = size.ws_row;
}

void printFile(string filename) {
    string line;
    ifstream myfile(filename.c_str());
    if (myfile.is_open()) {
        while (getline(myfile, line)) {
            cout << line << '\n';
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

string setOptions(int argc, char * argv[], bool *preserveAspectRatio, bool *interactive, FileType *fileType){
    string filename = "";
    for(int i = 0;i<argc;i++){
        //manual or automatic type logic, auto is still hacky
        if(strcmp(argv[i],"-image")==0){
            *fileType = IMG;
        }
        else if(strcmp(argv[i],"-video")==0){
            *fileType = IMG;
        }
        else if(strcmp(argv[i],"-doc")==0){
            *fileType = DOC;
        }
        else if(strcmp(argv[i],"-dir")==0){
            *fileType = DIR;
        }
        else if(strcmp(argv[i],"-dir")==0){
            *fileType = TXT;
        }
        else if(argv[i][0] != '-'){
            filename = argv[i];
            *fileType = getFileType(filename);
        }
        if(strcmp(argv[i],"-par")==0){
            *preserveAspectRatio = true;
        }
        if(strcmp(argv[i],"-i")==0){
            *interactive = true;
        }
    }
    return filename;
}

