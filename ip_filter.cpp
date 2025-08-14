// #include "version_lib.h"

#include <array>
#include <cassert>
#include <cstdint>
#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>


// ("",  '.') -> [""]
// ("11", '.') -> ["11"]
// ("..", '.') -> ["", "", ""]
// ("11.", '.') -> ["11", ""]
// (".11", '.') -> ["", "11"]
// ("11.22", '.') -> ["11", "22"]
std::vector<std::string> split(const std::string& str, const char d) {
    std::vector<std::string> r;

    std::string::size_type start = 0;
    std::string::size_type stop = str.find_first_of(d);
    while (stop != std::string::npos) {
        r.push_back(str.substr(start, stop - start));

        start = stop + 1;
        stop = str.find_first_of(d, start);
    }

    r.push_back(str.substr(start));

    return r;
}

/**
 * @brief Converts IP address string to uint8_t array
 * @param ip_string IP address string in dotted decimal format (e.g., "192.168.1.1")
 * @return Array of 4 uint8_t values representing the IP octets
 * @throws std::out_of_range if any octet is not in range [0, 255]
 * @throws std::invalid_argument if IP string format is invalid
 */
std::array<uint8_t, 4> stoi8(const std::string& ip_string) {
    const std::vector<std::string> ip_parts = split(ip_string, '.');
    if (ip_parts.size() != 4) {
        throw std::invalid_argument("IP address must have 4 octets");
    }
    std::array<uint8_t, 4> ip_octets{};
    size_t i = 0;
    for (const std::string& ip_s: ip_parts) {
        const int ip_int = std::stoi(ip_s);
        if (ip_int < 0 || ip_int > 255) {
            throw std::out_of_range("Value must be between 0 and 255");
        }
        ip_octets[i++] = static_cast<uint8_t>(ip_int);
    }
    return ip_octets;
}

// int main(int argc, char const *argv[])
int main() {
    try {

        using ip_p = std::pair<std::string, std::array<uint8_t, 4>>;
        std::vector<ip_p> ip_pool;

        for (std::string line; std::getline(std::cin, line);) {
            ip_p ip_pair;
            ip_pair.first = split(line, '\t').at(0);
            ip_pair.second = stoi8(ip_pair.first);
            ip_pool.push_back(ip_pair);
        }

        // reverse lexicographically sort
        auto compare_octets = [](const ip_p& a, const ip_p& b) -> bool { return a.second > b.second; };
        std::sort(ip_pool.begin(), ip_pool.end(), compare_octets);

        for (auto ip = ip_pool.cbegin(); ip != ip_pool.cend(); ++ip) {
            std::cout << ip->first << std::endl;
        }

        // 222.173.235.246
        // 222.130.177.64
        // 222.82.198.61
        // ...
        // 1.70.44.170
        // 1.29.168.152
        // 1.1.234.8

        // filter by first byte and output
        // ip = filter(1)
        for (auto ip = ip_pool.cbegin(); ip != ip_pool.cend(); ++ip) {
            if (ip->second[0] == 1) {
                std::cout << ip->first << std::endl;
            }
        }

        // 1.231.69.33
        // 1.87.203.225
        // 1.70.44.170
        // 1.29.168.152
        // 1.1.234.8

        // filter by first and second bytes and output
        // ip = filter(46, 70)
        for (auto ip = ip_pool.cbegin(); ip != ip_pool.cend(); ++ip) {
            if (ip->second[0] == 46 && ip->second[1] == 70) {
                std::cout << ip->first << std::endl;
            }
        }

        // 46.70.225.39
        // 46.70.147.26
        // 46.70.113.73
        // 46.70.29.76

        // filter by any byte and output
        // ip = filter_any(46)
        for (auto ip = ip_pool.cbegin(); ip != ip_pool.cend(); ++ip) {
            const auto is_46 = [](const uint8_t x) -> bool {return x == 46;};
            if (std::any_of(ip->second.cbegin(), ip->second.cend(), is_46)) {
                std::cout << ip->first << std::endl;
            }
        }

        // 186.204.34.46
        // 186.46.222.194
        // 185.46.87.231
        // 185.46.86.132
        // 185.46.86.131
        // 185.46.86.131
        // 185.46.86.22
        // 185.46.85.204
        // 185.46.85.78
        // 68.46.218.208
        // 46.251.197.23
        // 46.223.254.56
        // 46.223.254.56
        // 46.182.19.219
        // 46.161.63.66
        // 46.161.61.51
        // 46.161.60.92
        // 46.161.60.35
        // 46.161.58.202
        // 46.161.56.241
        // 46.161.56.203
        // 46.161.56.174
        // 46.161.56.106
        // 46.161.56.106
        // 46.101.163.119
        // 46.101.127.145
        // 46.70.225.39
        // 46.70.147.26
        // 46.70.113.73
        // 46.70.29.76
        // 46.55.46.98
        // 46.49.43.85
        // 39.46.86.85
        // 5.189.203.46
    } catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}