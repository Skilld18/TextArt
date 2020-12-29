#include <draw/draw.h>

int draw(Options options, std::string Filename)
{
    if (Filename.empty())
    {
        return 3;
    }
    if (!options.is_initialized())
    {
        return 4;
    }
    return 0;
}