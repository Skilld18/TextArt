#include <draw/draw.h>
#include <gtest/gtest.h>

TEST (DrawTest, Base)
{
    EXPECT_EQ (1, draw());
}
