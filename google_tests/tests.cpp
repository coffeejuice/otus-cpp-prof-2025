#include <gtest/gtest.h>
#include "../src/version_lib.h"
#include "../src/ip_filter.h"

TEST(StdVector, TestValidVersion) {

    EXPECT_GE(version(), 1);
}

// Add more tests for your ip_filter functions
TEST(IpFilter, TestSplit) {
    auto result = split("192.168.1.1", '.');
    EXPECT_EQ(result.size(), 4);
    EXPECT_EQ(result[0], "192");
    EXPECT_EQ(result[1], "168");
    EXPECT_EQ(result[2], "1");
    EXPECT_EQ(result[3], "1");
}

TEST(IpFilter, TestStoi8) {
    auto result = stoi8("192.168.1.1");
    EXPECT_EQ(result[0], 192);
    EXPECT_EQ(result[1], 168);
    EXPECT_EQ(result[2], 1);
    EXPECT_EQ(result[3], 1);
}
