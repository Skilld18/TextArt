#ifndef TEXTART_UTILS_H
#define TEXTART_UTILS_H

#include <string>

using namespace ::std;

enum FileType{
    IMG, //Pictures like jpg and png
    VID, //Videos like mp4
    DOC, //PDFs and the like that can be converted to imgs
    DIR, //A directory
    TXT, //Text and binary files that this program can't do anything to
    NONE, //Can't be opened or does't exist
};

const string image_types[] = {".jpg", ".png"};
const string vid_types[] = {".mp4", ".avi"};
const string doc_types[] = {".pdf", ".doc"};
FileType getFileType(string filename);
void printFile(string filename);
void getTerminalSize(int &termWidth, int &termHeight);
char getch();
string setOptions(int argc, char * argv[], bool *preserveAspectRatio, bool *interactive, FileType *fileType);

#endif //TEXTART_UTILS_H
