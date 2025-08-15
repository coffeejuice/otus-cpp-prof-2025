#pragma once

#include <array>
#include <cstdint>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <functional>

using ip_p = std::pair<std::string, std::array<uint8_t, 4>>;

std::vector<std::string> split(const std::string& str, const char d);
std::array<uint8_t, 4> stoi8(const std::string& ip_string);
bool compare_first_bytes(const ip_p &ip, const std::initializer_list<uint8_t> bytes_);
bool compare_any_bytes(const ip_p &ip, const std::initializer_list<uint8_t> bytes_);

struct FilterClosure {
    const std::vector<ip_p>& input_data;
    std::ostream& output_stream;

    explicit FilterClosure(
        const std::vector<ip_p>& input_data,
        std::ostream& output_stream
        ) : input_data(input_data), output_stream(output_stream) {}

    void operator()(
        const std::function<bool(const ip_p&, const std::initializer_list<uint8_t>&)>& filter,
        const std::initializer_list<uint8_t> bytes
        ) const;
};