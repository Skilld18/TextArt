#ifndef TEXTART_IMAGE_H
#define TEXTART_IMAGE_H

#include <string>

#include <opencv2/opencv.hpp>

using namespace ::cv;
using namespace ::std;

string createPixel(Vec3b colour, string glyph);
string matToPixels(Mat mat);
string matToPixels(Mat mat, string c);
string matToPixels(Mat mat, string (*charAtPos)(int, int));

#endif //TEXTART_IMAGE_H
