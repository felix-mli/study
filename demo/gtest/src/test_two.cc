#include "gtest/gtest.h"

TEST(TEST_TWO, Test1) {
    int a = 1;
    int b = 2;
    int c = 5;
    EXPECT_NE((a + b), c);
}

TEST(TEST_TWO, Test2) {
    int a = 3;
    int b = 4;
    int c = 7;
    EXPECT_EQ((a + b), c);
}

TEST(TEST_TWO, Test3) {
    GTEST_SKIP() << "Skipping this test just to test for GTEST_SKIP() function";
    int a = 5;
    int b = 6;
    int c = 11;
    EXPECT_EQ((a + b), c);
}