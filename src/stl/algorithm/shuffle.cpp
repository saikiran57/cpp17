/**
 * @file shuffle.cpp
 * @author Saikiran Nadipilli
 * @brief
 * @version 0.1
 * @date 2024-05-18
 *
 * @copyright Copyright (c) 2024
 *
 */

/**
 * @brief https://en.cppreference.com/w/cpp/algorithm/random_shuffle
 *
 */

#include <algorithm>
#include <iostream>
#include <random>
#include <vector>

int main()
{
    std::vector<int> vec{1, 2, 3, 4, 5, 6, 7, 8, 9};

    auto printContainer = [](const std::vector<int> vec) {
        for (auto&& i : vec)
        {
            std::cout << i << "\n";
        }
    };

    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(vec.begin(), vec.end(), g);

    printContainer(vec);
}
