#include "../include/draw/options.h"
#include <cstdlib>
#include <vector>
#include <iostream>

bool parse_options(std::vector<std::string> &args, Options &options)
{
    options.set_AspectRatio(false);
    options.set_interactive(false);
    options.set_height(30);
    options.set_width(30);
    options.set_outputMode(Options::BW);
    options.set_colourSpace(Options::BIN);
    options.set_type(Options::IMAGE);
    for (const auto &s: args) {
        if (s == "-p") {
            options.set_AspectRatio(true);
        }
        else if (s == "-i") {
            options.set_interactive(true);
        }
        else if (s.substr(0, 2) == "-h") {
            try {
                options.set_height(static_cast<unsigned int>(atoi(s.substr(2).c_str())));
            }
            catch (std::exception &e) {
                return false;
            }
        }
        else if (s.substr(0, 2) == "-w") {
            try {
                options.set_width(static_cast<unsigned int>(atoi(s.substr(2).c_str())));
            }
            catch (std::exception &e) {
                return false;
            }
        }
        else if (s == "--image") {
            options.set_type(Options::IMAGE);
        }
        else if (s == "--text") {
            options.set_type(Options::TEXT);
        }
        else if (s == "--doc") {
            options.set_type(Options::DOCUMENT);
        }
        else if (s == "--audio") {
            options.set_type(Options::AUDIO);
        }
        else if (s == "--video") {
            options.set_type(Options::VIDEO);
        }
        else if (s == "--bash8") {
            options.set_colourSpace(Options::BASH8);
        }
        else if (s == "--bash24") {
            options.set_colourSpace(Options::BASH24);
        }
        else if (s == "--bin") {
            options.set_colourSpace(Options::BIN);
        }
        else if (s == "--html") {
            options.set_colourSpace(Options::HTML);
        }
        else if (s == "--bw") {
            options.set_outputMode(Options::BW);
        }
        else if (s == "--colour") {
            options.set_outputMode(Options::COLOUR);
        }
        else {
            return false;
        }
    }
    return options.is_initialized();
}

bool parse_file(std::vector<std::string> &args, std::string &data)
{
    for (size_t i = 0; i < args.size(); i++) {
        if (args[i][0] != '-') {
            data = args[i];
            args.erase(args.begin() + static_cast<long>(i));
        }
    }
    return !data.empty();
}
