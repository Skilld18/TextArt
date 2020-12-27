#include <draw/options.h>
#include <gtest/gtest.h>
#include <climits>

const char * const settingsList[] = {
"aspectRatio",
"interactive",
"height",
"width",
"type",
"colourSpace",
"outputMode"
};

TEST (OptionsTests, HowManyOptions) // NOLINT
{
    class TesterClass : public Options
    {
    public:
        std::map<std::string, int> get_options()
        {
            return options;
        }
        
    };

    TesterClass tester;
    Options options;
    auto dict = tester.get_options();
    std::map<std::string, int> mock;
    for (const auto &option : settingsList)
    {
        mock[option] = -1;
    }
    EXPECT_EQ(dict, mock);
}

TEST (OptionsTests, GetterSetter) // NOLINT
{
    Options options;
    EXPECT_FALSE(options.is_initialized());
    options.set_AspectRatio(true);
    options.set_interactive(true);
    options.set_height(0);
    options.set_width(0);
    options.set_type(Options::IMAGE);
    options.set_colourSpace(Options::BASH8);
    EXPECT_FALSE(options.is_initialized());
    options.set_outputMode(Options::BW);
    EXPECT_TRUE(options.is_initialized());
}

TEST (OptionsTests, GetterSetterDifferentOrder) // NOLINT
{
    Options options;
    EXPECT_FALSE(options.is_initialized());
    options.set_AspectRatio(true);
    options.set_interactive(true);
    options.set_height(1);
    options.set_width(0);
    options.set_type(Options::IMAGE);
    options.set_outputMode(Options::BW);
    EXPECT_FALSE(options.is_initialized());
    options.set_colourSpace(Options::BASH8);
    EXPECT_TRUE(options.is_initialized());
}

TEST (OptionsTests, UsingGetterSetter) // NOLINT
{
    Options options;
    options.set_AspectRatio(true);
    options.set_AspectRatio(false);
    EXPECT_FALSE(options.get_AspectRatio());
    options.set_AspectRatio(true);
    EXPECT_TRUE(options.get_AspectRatio());

    options.set_interactive(true);
    options.set_interactive(false);
    EXPECT_FALSE(options.get_interactive());
    options.set_interactive(true);
    EXPECT_TRUE(options.get_interactive());
    
    options.set_height(1);
    options.set_height(0);
    EXPECT_EQ(options.get_height(), 0);
    options.set_height(UINT_MAX);
    EXPECT_EQ(options.get_height(), UINT_MAX);
    
    options.set_width(1);
    options.set_width(0);
    EXPECT_EQ(options.get_width(), 0);
    options.set_width(UINT_MAX);
    EXPECT_EQ(options.get_width(), UINT_MAX);

}

TEST(OptionsTests, Type) // NOLINT
{
    Options options;
    const int last_enum = Options::VIDEO;
    options.set_type(static_cast<Options::Type>(last_enum));

    for (int i = 0;i<=last_enum;i++)
    {
        options.set_type(static_cast<Options::Type>(i));
        EXPECT_EQ(options.get_type(), i);
    }

    Options::Type t = Options::TEXT;
    switch (t)
    {
        case Options::IMAGE:
        case Options::TEXT:
        case Options::DOCUMENT:
        case Options::AUDIO:
        case (Options::Type) last_enum:
            break;
    }
}

TEST(OptionsTests, ColourSpace) // NOLINT
{
    Options options;
    const int last_enum = Options::HTML;
    options.set_colourSpace(static_cast<Options::ColourSpace>(last_enum));

    for (int i = 0;i<=last_enum;i++)
    {
        options.set_colourSpace(static_cast<Options::ColourSpace>(i));
        EXPECT_EQ(options.get_colourSpace(), i);
    }

    Options::ColourSpace t = Options::BASH24;
    switch (t)
    {
    case Options::BASH8:
    case Options::BASH24:
    case (Options::ColourSpace) last_enum:
        break;
    }
}

TEST(OptionsTests, OutputMode) // NOLINT
{
    Options options;
    const int last_enum = Options::COLOUR;
    options.set_outputMode(static_cast<Options::OutputMode>(last_enum));

    for (int i = 0;i<=last_enum;i++)
    {
        options.set_outputMode(static_cast<Options::OutputMode>(i));
        EXPECT_EQ(options.get_outputMode(), i);
    }

    Options::OutputMode t = Options::COLOUR;
    switch (t)
    {
    case Options::BW:
    case (Options::OutputMode) last_enum:
        break;
    }
}
