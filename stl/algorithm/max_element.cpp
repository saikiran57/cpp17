/**
 * @file max_element.cpp
 * @author Saikiran Nadipilli
 * @brief
 * @version 0.1
 * @date 2024-11-23
 *
 * @copyright Copyright (c) 2024
 *
 */

#include <algorithm>
#include <cmath>
#include <iostream>
#include <iterator>
#include <vector>

int main()
{
    std::vector<int> v{3, 1, -14, 1, 5, 9, -14, 9};
    std::vector<int>::iterator result;

    result = std::ranges::max_element(v, );
    std::cout << "Max element found at index " << std::distance(v.begin(), result) << " has value " << *result << '\n';

    result = std::ranges::max_element(v, , [](int a, int b) {
        return std::abs(a) < std::abs(b);
    });
    std::cout << "Absolute max element found at index " << std::distance(v.begin(), result) << " has value " << *result
              << '\n';
}