#include <draw/options.h>
#include <string>
#include <opencv2/core/matx.hpp>


int draw(Options &options, const std::string &filename);
std::string draw_pixel(const cv::Vec<unsigned char, 3> vec, const std::string &glyph, const Options::ColourSpace cs);
std::string draw_newline();
std::string get_glyph();
Options::ColourSpace get_colourspace();

