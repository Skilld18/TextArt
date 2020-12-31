#include "../apps/parse.h"
#include <gtest/gtest.h>


TEST (ParseTests, File) // NOLINT
{
    std::vector<std::string> args;
    Options options;
    std::string data;
    args.emplace_back("Filename");
    parse_file(args, data);
    EXPECT_EQ(data, "Filename");
}

TEST (ParseTests, options) // NOLINT
{
    std::vector<std::string> args;
    Options options;
    EXPECT_TRUE(parse_options(args, options));
    EXPECT_FALSE(options.get_AspectRatio());
    EXPECT_FALSE(options.get_interactive());
    EXPECT_EQ(options.get_height(), 30);
    EXPECT_EQ(options.get_width(), 30);
    EXPECT_EQ(options.get_type(), Options::IMAGE);
    EXPECT_EQ(options.get_colourSpace(), Options::BIN);
    EXPECT_EQ(options.get_outputMode(), Options::BW);
    args.emplace_back("-p");
    args.emplace_back("-i");
    args.emplace_back("-h40");
    args.emplace_back("-w40");
    args.emplace_back("--image");
    args.emplace_back("--text");
    args.emplace_back("--doc");
    args.emplace_back("--audio");
    args.emplace_back("--video");
    args.emplace_back("--bin");
    args.emplace_back("--bash8");
    args.emplace_back("--bash24");
    args.emplace_back("--html");
    args.emplace_back("--bw");
    args.emplace_back("--colour");
    EXPECT_TRUE(parse_options(args, options));
    EXPECT_TRUE(options.get_AspectRatio());
    EXPECT_TRUE(options.get_interactive());
    EXPECT_EQ(options.get_height(), 40);
    EXPECT_EQ(options.get_width(), 40);
    EXPECT_EQ(options.get_type(), Options::VIDEO);
    EXPECT_EQ(options.get_colourSpace(), Options::HTML);
    EXPECT_EQ(options.get_outputMode(), Options::COLOUR);

    args.emplace_back("-n");
    EXPECT_FALSE(parse_options(args, options));
    args.emplace_back("-h");
    EXPECT_FALSE(parse_options(args, options));
    args.pop_back();
    args.emplace_back("-w345w");
    EXPECT_FALSE(parse_options(args, options));
}
