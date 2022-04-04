#include "draw/draw.h"
#include <gtest/gtest.h>

TEST (DrawPixelTests, glyph) // NOLINT
{
    std::vector<std::string> args;
    Options o;
    EXPECT_EQ(get_glyph(), "\u2588");
}

TEST (DrawPixelTests, Colourspace) // NOLINT
{
    Options o;
    o.set_colourSpace(Options::BASH24);
    EXPECT_EQ(get_colourspace(), Options::BASH24);
}

