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
#include <vector>

int main()
{
    std::vector<int> v{3, 1, -14, 1, 5, 9, -14, 9};
    std::vector<int>::iterator result;

    result = std::max_element(v.begin(), v.end());
    std::cout << "Max element found at index " << std::distance(v.begin(), result) << " has value " << *result << '\n';

    result = std::max_element(v.begin(), v.end(), [](int a, int b) {
        return std::abs(a) < std::abs(b);
    });
    std::cout << "Absolute max element found at index " << std::distance(v.begin(), result) << " has value " << *result
              << '\n';
}