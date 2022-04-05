#include <draw/draw.h>
#include <iostream>

int main(int argc, const char *argv[])
{
    if (argc < 2)
    {
        std::cerr << "Requires a file" << std::endl;
        return 1;
    }
    return draw(argv[1]);
}