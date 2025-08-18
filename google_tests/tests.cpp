#include <gtest/gtest.h>
#include "../src/version_lib.h"
#include "../src/ip_filter.h"

#include <sstream>

TEST(VersionLib, TestValidVersion) {
    EXPECT_GE(version(), 1);
}

// Add more tests for your ip_filter functions
TEST(IpFilterLib, TestSplitFileLine) {
    const auto result = split("113.162.145.156	111	0", '\t');
    EXPECT_EQ(result.size(), 3);
    EXPECT_EQ(result[0], "113.162.145.156");
    EXPECT_EQ(result[1], "111");
    EXPECT_EQ(result[2], "0");
}

// Add more tests for your ip_filter functions
TEST(IpFilterLib, TestSplitIP) {
    const auto result = split("192.168.1.1", '.');
    EXPECT_EQ(result.size(), 4);
    EXPECT_EQ(result[0], "192");
    EXPECT_EQ(result[1], "168");
    EXPECT_EQ(result[2], "1");
    EXPECT_EQ(result[3], "1");
}

TEST(IpFilterLib, TestStoi8) {
    const auto result = stoi8("192.168.1.1");
    EXPECT_EQ(result[0], 192);
    EXPECT_EQ(result[1], 168);
    EXPECT_EQ(result[2], 1);
    EXPECT_EQ(result[3], 1);
}

TEST(IpFilterLib, TestCompareFirstBytes) {
    const ip_p pair = {"", {192, 168, 1, 1}};

    const auto false_result_one_byte = compare_first_bytes(pair, {10});
    EXPECT_EQ(false_result_one_byte, false);

    const auto true_result_one_byte = compare_first_bytes(pair, {192});
    EXPECT_EQ(true_result_one_byte, true);

    const auto false_result_two_byte_1 = compare_first_bytes(pair, {10, 100});
    EXPECT_EQ(false_result_two_byte_1, false);

    const auto false_result_two_byte_2 = compare_first_bytes(pair, {192, 100});
    EXPECT_EQ(false_result_two_byte_2, false);

    const auto false_result_two_byte_3 = compare_first_bytes(pair, {10, 168});
    EXPECT_EQ(false_result_two_byte_3, false);

    const auto true_result_two_byte = compare_first_bytes(pair, {192, 168});
    EXPECT_EQ(true_result_two_byte, true);
}

TEST(IpFilterLib, TestCompareAnyBytes) {
    const ip_p pair = {"", {192, 168, 1, 1}};

    const auto false_result = compare_any_bytes(pair, {100});
    EXPECT_EQ(false_result, false);

    const auto true_result = compare_any_bytes(pair, {1});
    EXPECT_EQ(true_result, true);
}

// Create a test fixture class
class IpFilterLibClosureTest : public ::testing::Test {
protected:
    void SetUp() override {
        // Clear the stringstream before each test
        ss.str("");
        ss.clear();
    }

    void TearDown() override {
        // Optional cleanup after each test
    }

    // Shared variables
    std::stringstream ss;
    const std::vector<ip_p> ip_pool = {
        {"192.168.1.1", {192, 168, 1, 1}},
        {"85.254.10.197", {85, 254, 10, 197}},
        {"67.250.31.212", {67, 250, 31, 212}},
        {"182.75.81.122", {182, 75, 81, 122}},
        {"30.168.75.1", {30, 168, 75, 1}},
    };
};

// Now use TEST_F instead of TEST
TEST_F(IpFilterLibClosureTest, TestFilterClosureNoFilter) {
    const auto cout_filter = FilterClosure(ip_pool, ss);

    const std::string expected = "192.168.1.1\n85.254.10.197\n67.250.31.212\n182.75.81.122\n30.168.75.1\n";
    cout_filter([](const ip_p&, const std::initializer_list<uint8_t>){return true;}, {});

    EXPECT_EQ(ss.str(), expected);
}

TEST_F(IpFilterLibClosureTest, TestFilterClosureOneByte) {
    const auto cout_filter = FilterClosure(ip_pool, ss);

    cout_filter(compare_first_bytes, {192});
    EXPECT_EQ(ss.str(), "192.168.1.1\n");

    // Clear the stream and add another test case
    ss.str("");
    ss.clear();

    cout_filter(compare_first_bytes, {85});
    EXPECT_EQ(ss.str(), "85.254.10.197\n");

    // Clear the stream and add another test case
    ss.str("");
    ss.clear();

    cout_filter(compare_first_bytes, {100});
    EXPECT_EQ(ss.str(), "");
}

TEST_F(IpFilterLibClosureTest, TestFilterClosureTwoBytes) {
    const auto cout_filter = FilterClosure(ip_pool, ss);

    cout_filter(compare_first_bytes, {192, 168});
    EXPECT_EQ(ss.str(), "192.168.1.1\n");

    // Clear the stream and add another test case
    ss.str("");
    ss.clear();

    cout_filter(compare_first_bytes, {85, 254});
    EXPECT_EQ(ss.str(), "85.254.10.197\n");

    // Clear the stream and add another test case
    ss.str("");
    ss.clear();

    cout_filter(compare_first_bytes, {85, 1});
    EXPECT_EQ(ss.str(), "");
}

TEST_F(IpFilterLibClosureTest, TestFilterClosureAnyByte) {
    const auto cout_filter = FilterClosure(ip_pool, ss);

    cout_filter(compare_any_bytes, {75});
    EXPECT_EQ(ss.str(), "182.75.81.122\n30.168.75.1\n");

    // Clear the stream and add another test case
    ss.str("");
    ss.clear();

    cout_filter(compare_any_bytes, {168});
    EXPECT_EQ(ss.str(), "192.168.1.1\n30.168.75.1\n");

    // Clear the stream and add another test case
    ss.str("");
    ss.clear();

    cout_filter(compare_any_bytes, {100});
    EXPECT_EQ(ss.str(), "");
}


