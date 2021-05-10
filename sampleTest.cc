#include <gtest/gtest.h>
#include "sample.h"

TEST(testFunc, valueIs1) {
    EXPECT_EQ(testFunc(1), 2);
    EXPECT_NE(testFunc(1), 1);
}

TEST(testFunc, valueIs2) {
    EXPECT_EQ(testFunc(2), 4);
    EXPECT_NE(testFunc(2), 2);
}
