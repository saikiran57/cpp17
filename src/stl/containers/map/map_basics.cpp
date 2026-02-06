/**
 * @file map_basics.cpp
 * @author Saikiran Nadipilli
 * @brief
 * @version 0.1
 * @date 2024-05-18
 *
 * @copyright Copyright (c) 2024
 *
 */

#include <iostream>
#include <string>
#include <unordered_map>

int main()
{
    std::string const s("testtest");
    std::unordered_map<char, int> map;

    for (auto c : s)
    {
        ++map[c];
    }

    for (auto [k, v] : map)
    {
        std::cout << "K:" << k << " V:" << v << "\n";
    }
}
