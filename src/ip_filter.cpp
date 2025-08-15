#include "ip_filter.h"

// int main(int argc, char const *argv[])
int main() {
    try {

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

        auto& os = std::cout;
        const auto cout_filter = FilterClosure(ip_pool, os);

        cout_filter([](const ip_p&, const std::initializer_list<uint8_t>){return true;}, {});
        cout_filter(compare_first_bytes, {1});
        cout_filter(compare_first_bytes, {46, 70});
        cout_filter(compare_any_bytes, {46});

    } catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}