#include "image.h"

string createPixel(Vec3b colour, string glyph) {
    stringstream pixel;
    pixel << "\x1b[38;2;" << (int)colour[2] << ";" << (int)colour[1] << ";" << (int)colour[0] << "m" << glyph << "\x1b[0m";
    return pixel.str();
}

//TODO:: Glyph rules
string matToPixels(Mat mat) {
    string t = "\033[0;0f";
    for (int i = 0; i < mat.size().height; i++) {
        for (int j = 0; j< mat.size().width; j++) {
            Vec3b intensity = mat.at<Vec3b>(i, j);
            t += createPixel(intensity, "a");
        }
        t += '\n';
    }
    return t;
}
