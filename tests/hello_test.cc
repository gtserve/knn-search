#include <gtest/gtest.h>

TEST(HelloTestSuite, BasicTest1) {
    EXPECT_STRNE("hello", "world");
}

TEST(HelloTestSuite, BasicTest2) {
    EXPECT_EQ(7 * 6, 42);
}
