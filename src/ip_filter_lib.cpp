#include "ip_filter.h"


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
 * @brief Converts IP address string to an uint8_t array
 * @param ip_string IP address string in dotted decimal format (e.g., "192.168.1.1")
 * @return Array of 4 uint8_t values representing the IP octets
 * @throws std::out_of_range if any octet is not in range [0, 255]
 * @throws std::invalid_argument if the IP string format is invalid
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

bool compare_first_bytes(const ip_p &ip, const std::initializer_list<uint8_t> bytes_) {
    if (bytes_.size() == 0 || bytes_.size() > ip.second.size()) {
        return false;
    }
    return std::equal(bytes_.begin(), bytes_.end(), ip.second.begin());
}

bool compare_any_bytes(const ip_p &ip, const std::initializer_list<uint8_t> bytes_) {
    auto func_ = [bytes_](const uint8_t x) -> bool {return x == *bytes_.begin();};
    return std::any_of(ip.second.cbegin(), ip.second.cend(), func_);
}

void FilterClosure::operator()(
    const std::function<bool(const ip_p&, const std::initializer_list<uint8_t>&)>& filter,
    const std::initializer_list<uint8_t> bytes
    ) const {
    for (const auto& ip : input_data) {
        if (filter(ip, bytes)) {
            output_stream << ip.first << std::endl;
        }
    }
}
