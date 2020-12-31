#include <draw/draw.h>
#include <gtest/gtest.h>
#include <fstream>


TEST(DrawTests, pixel) // NOLINT
{
    EXPECT_EQ(draw_pixel("r"), "r");
    const std::string rectangle = "\u2588";
    EXPECT_EQ(draw_pixel(rectangle), "█");
}

TEST(DrawTests, newline) // NOLINT
{
    EXPECT_EQ(draw_newline(), "\n");
}

TEST(DrawTests, sunflowers) // NOLINT
{
    Options options;
    options.set_AspectRatio(true);
    options.set_interactive(true);
    options.set_height(1);
    options.set_width(0);
    options.set_type(Options::IMAGE);
    options.set_colourSpace(Options::BIN);
    options.set_outputMode(Options::BW);
    testing::internal::CaptureStdout();
    const std::string path = "../../tests/sunflowers.jpg";
    EXPECT_EQ(draw(options, path), 0);
    std::string output = testing::internal::GetCapturedStdout();

    std::ifstream ifs("../../tests/sunflowers.txt");
    std::string content((std::istreambuf_iterator<char>(ifs)),
                        (std::istreambuf_iterator<char>()));
    EXPECT_EQ(output, content);
} 

TEST(DrawTests, nofile) // NOLINT
{
    Options options;
    EXPECT_EQ(draw(options, ""), 3);
    options.set_AspectRatio(true);
    options.set_interactive(true);
    options.set_height(1);
    options.set_width(0);
    options.set_type(Options::IMAGE);
    options.set_colourSpace(Options::BIN);
    options.set_outputMode(Options::BW);
    EXPECT_EQ(draw(options, "filename"), 4);
}