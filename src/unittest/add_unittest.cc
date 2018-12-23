#include <gtest/gtest.h>
#include "add.h"

TEST(testCase, test0)
{
    EXPECT_EQ(add(2, 3), 5);
}

TEST(testCase, test1)
{
    EXPECT_EQ(add(2, 3), 6);
}
