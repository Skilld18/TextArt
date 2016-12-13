#ifndef TEXTART_UTILS_H
#define TEXTART_UTILS_H

#include <string>
#include <vector>

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
void printFile(string filename, int start, int end);
void getTerminalSize(int &termWidth, int &termHeight);
char getch();
string setOptions(vector<string> args, bool *preserveAspectRatio, bool *interactive, bool *writeToFile, FileType *fileType);
void userInput(int *frame, int *panX, int *panY, float *zoom_ratio, int imgWidth, int imgHeight);
#endif //TEXTART_UTILS_H
