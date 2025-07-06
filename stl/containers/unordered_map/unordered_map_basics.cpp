/**
 * @file unordered_map_basics.cpp
 * @author Saikiran Nadipilli
 * @brief
 * @version 0.1
 * @date 2025-01-16
 *
 * @copyright Copyright (c) 2025
 *
 */

/**
 * @brief https://en.cppreference.com/w/cpp/container/unordered_map/unordered_map
 *
 * https://medium.com/@gulshansharma014/call-to-implicitly-deleted-default-constructor-of-unordered-map-pair-int-int-int-d3b2a6da0b41
 *
 * https://godbolt.org/z/oT5sP7eWG
 */

#include <bitset>
#include <cstddef>
#include <iostream>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>

struct StringHasher
{
    std::size_t operator()(const std::string& s) const
    {
        std::cout << "custom hashing\n";
        return std::hash<std::string>{}(s);
    }
};

int main()
{
    // std::unordered_map<std::string, std::string, StringHasher> umap;

    // umap["abc"] = "cba";

    // std::cout << "value: " << umap["abc"] << std::endl;

    // range constructor
    std::vector<std::pair<std::bitset<8>, int>> v = {{0x12, 1}, {0x01, -1}};
    std::unordered_map<std::bitset<8>, int> m5(v.begin(), v.end());

    for (auto&& [key, value] : m5)
    {
        std::cout << " key: " << key;
    }

    return 0;
}
