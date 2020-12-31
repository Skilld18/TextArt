#include <draw/draw.h>
#include <iostream>
#include "parse.h"

int main(int argc, const char *argv[])
{
    Options options;
    std::vector<std::string> arguments(argv + 1, argv + argc);
    std::string Filename;

    if (!parse_file(arguments, Filename)) {
        std::cout << "Bad file" << std::endl;
        return 1;
    }

    if (!parse_options(arguments, options)) {
        std::cout << "Bad options" << std::endl;
        return 2;
    }
    return draw(options, Filename);
}