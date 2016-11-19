#include "utils.h"

#include <iostream>
#include <fstream>
#include <sys/ioctl.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string>



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

//TODO:: I've yet to find a consistent way to do this so ...
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
