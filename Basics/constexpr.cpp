/**
 * @file constexpr.cpp
 * @author Saikiran Nadipilli
 * @brief
 * @version 0.1
 * @date 2024-10-18
 *
 * @copyright Copyright (c) 2024
 *
 */

/**
 * @brief https://iamsorush.com/posts/cpp-constexpr/
 *
 */

#include <array>
#include <iostream>

static constexpr auto ARRAY_SIZE = 4;
static constexpr std::array<char, ARRAY_SIZE> a{'1', '2', '3', '4'};

constexpr auto get(int n)
{
    return a[n];
}

int main()
{
    constexpr auto temp = 2;
    constexpr auto value = get(5);
    // static_assert(value > 4, "out of range");
    std::cout << value;
    return 0;
}