#include <gtest/gtest.h>
#include "../src/version_lib.h"
#include "../src/ip_filter.cpp"

TEST(StdVector, TestValidVersion) {

    EXPECT_GE(version(), 1);
}

