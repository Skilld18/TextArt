#include "utils.h"

#include <sys/ioctl.h>
#include <unistd.h>

//TODO:: Sort by filetpye and return a Enum Mat pair
FileType getFileType(string filename){
    if (1)
        return IMG;
    else if(0)
        return VID;
    else if(0)
        return DOC;
    else if(0)
        return DIR;
    else if(1)
        return TXT;
    return NONE;
}

void getTerminalSize(int &termWidth, int &termHeight){
    struct winsize size;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &size);
    termWidth = size.ws_col;
    termHeight = size.ws_row;
}

