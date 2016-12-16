#include "image.h"

string createPixel(Vec3b colour, string glyph) {
    stringstream pixel;
    //set background colour not text colour
    if (glyph.empty()){
        pixel << "\e[48;2;" << (int)colour[2] << ";" <<(int) colour[1] << ";" << (int) colour[0] <<"m ";
    }
        //reset background and then draw colour characters
    else {
        pixel << "\e[49m" << "\x1b[38;2;" << (int) colour[2] << ";" << (int) colour[1] << ";" << (int) colour[0] << "m" << glyph << "\x1b[0m";
    }
    return pixel.str();
}

//8 and 16 colour logic basically rounding to the nearest predefined colour
/*string createPixel(Vec3b colour, string glyph) {
    stringstream pixel;
    int c = (colour[0]/128 * 4) + (colour[1]/128*2) + (colour[2]/128);
    if(c == 7){
        c = (colour[0]/200* 4) + (colour[1]/200*2) + (colour[2]/200);
        pixel << "\e[" << 99 + c << "m" << glyph;
    }
    else{
        pixel << "\e[" << 40 + c << "m" << glyph;
    }
    return pixel.str();
}*/

string returnBlock(string ch){
    return ch;
}

string matToPixels(Mat mat) {
    return matToPixels(mat, returnBlock(""));
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
