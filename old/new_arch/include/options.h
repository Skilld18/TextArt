#ifndef LIBDRAW_OPTIONS_H
#define LIBDRAW_OPTIONS_H

#include <vector>
#include <ios>
#include "colourspace.h"
#include "transform.h"

class Options
{
public:

    //sizing
    static bool preserveAspectRatio;
    static int height;
    static int width;
    static bool interactive;

    //media type
    enum Type {IMAGE, TEXT, DOCUMENT, AUDIO, VIDEO};
    static Type type;


    //simple transforms applied
    static std::vector<transform> transforms;

    //output mode
    static colourspace *cs;

};

#endif //LIBDRAW_OPTIONS_H
