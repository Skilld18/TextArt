#include <map>
#pragma once
class Options
{
public:

    enum Type
    {
        IMAGE, TEXT, DOCUMENT, AUDIO, VIDEO
    };

    enum ColourSpace
    {
        BIN, BASH8, BASH24, HTML
    };

    enum OutputMode
    {
        BW, COLOUR
    };

    void set_AspectRatio(const bool ar)
    {
        options["aspectRatio"] = ar;
    }

    bool get_AspectRatio()
    {
        return static_cast<bool>(options["aspectRatio"]);
    }

    void set_interactive(const bool i)
    {
        options["interactive"] = i;
    }

    bool get_interactive()
    {
        return static_cast<bool>(options["interactive"]);
    }

    void set_height(const uint height)
    {
        options["height"] = static_cast<int>(height);
    }

    uint get_height()
    {
        return static_cast<uint>(options["height"]);
    }

    void set_width(const uint width)
    {
        options["width"] = static_cast<int>(width);
    }

    uint get_width()
    {
        return static_cast<uint>(options["width"]);
    }

    void set_type(const Type t)
    {
        options["type"] = t;
    }

    Type get_type()
    {
        return static_cast<Type>(options["type"]);
    }

    void set_colourSpace(ColourSpace c)
    {
        options["colourSpace"] = c;
    }

    ColourSpace get_colourSpace()
    {
        return static_cast<ColourSpace>(options["colourSpace"]);
    }

    void set_outputMode(OutputMode o)
    {
        options["outputMode"] = o;
    }

    OutputMode get_outputMode()
    {
        return static_cast<OutputMode>(options["outputMode"]);
    }

    bool is_initialized()
    {
        bool done = true;
        for (const auto &option:options) {
            if (option.second == -1) {
                done = false;
            }
        }
        return done;
    }

protected:
    std::map<std::string, int> options = {
        {"aspectRatio", -1},
        {"interactive", -1},
        {"height", -1},
        {"width", -1},
        {"type", -1},
        {"colourSpace", -1},
        {"outputMode", -1},
    };
};