#include "image.h"

string createPixel(Vec3b colour, string glyph) {
    stringstream pixel;
    //pixel << "\x1b[38;2;" << (int)colour[2] << ";" << (int)colour[1] << ";" << (int)colour[0] << "m" << glyph << "\x1b[0m";
    //alternate method of colouring the screen by setting background colour
    pixel << "\e[48;2;" << (int)colour[2] << ";" <<(int) colour[1] << ";" << (int) colour[0] <<"m ";
    return pixel.str();
}

string returnBlock(string ch){
    return ch;
}

string matToPixels(Mat mat) {
    return matToPixels(mat, returnBlock("\u25AF"));
}

string matToPixels(Mat mat, string c) {
    return matToPixels(mat, returnBlock(c));
}

//TODO:: Deal with terminals with limited colour
//TODO:: Filters? Effects?
string matToPixels(Mat mat, string (*charAtPos)(int, int)) {
    string t;
    for (int i = 0; i < mat.size().height; i++) {
        for (int j = 0; j< mat.size().width; j++) {
            Vec3b intensity = mat.at<Vec3b>(i, j);
                t += createPixel(intensity, charAtPos(i,j));
        }
        t += '\n';
    }
    t = t.substr(0,t.length()-1);
    t +="\033[0;0f";
    return t;
}
