/**
 * @file string_view.cpp
 * @author Saikiran Nadipilli
 * @brief
 * @version 0.1
 * @date 2024-10-18
 *
 * @copyright Copyright (c) 2024
 *
 */

#include <iostream>
#include <string_view>

int main()
{
    using namespace std::literals;  // easiest way to access the s and sv suffixes

    constexpr std::string_view sv1 = "my test code";
    constexpr auto sv2 = "my test code";

    static_assert(sv1 == sv2, "not equal");

    std::cout << "sv1: " << sv1 << "\n";
    std::cout << "sv2: " << sv2 << "\n";

    return 0;
}