#include "../apps/parse.h"
#include <gtest/gtest.h>
#include <vector>


TEST (ParseTests, File) // NOLINT
{
    std::vector<std::string> args;
    Options options;
    std::string data;
    args.push_back("Filename");
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
    args.push_back("-p");
    args.push_back("-i");
    args.push_back("-h40");
    args.push_back("-w40");
    args.push_back("--image");
    args.push_back("--text");
    args.push_back("--doc");
    args.push_back("--audio");
    args.push_back("--video");
    args.push_back("--bin");
    args.push_back("--bash8");
    args.push_back("--bash24");
    args.push_back("--html");
    args.push_back("--bw");
    args.push_back("--colour");
    EXPECT_TRUE(parse_options(args, options));
    EXPECT_TRUE(options.get_AspectRatio());
    EXPECT_TRUE(options.get_interactive());
    EXPECT_EQ(options.get_height(), 40);
    EXPECT_EQ(options.get_width(), 40);
    EXPECT_EQ(options.get_type(), Options::VIDEO);
    EXPECT_EQ(options.get_colourSpace(), Options::HTML);
    EXPECT_EQ(options.get_outputMode(), Options::COLOUR);
    
    args.push_back("-n");
    EXPECT_FALSE(parse_options(args, options));
    args.push_back("-h");
    EXPECT_FALSE(parse_options(args, options));
    args.pop_back();
    args.push_back("-w345w");
    EXPECT_FALSE(parse_options(args, options));
}
