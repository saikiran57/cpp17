/**
 * @file search.cpp
 * @author Saikiran Nadipilli
 * @brief https://en.cppreference.com/w/cpp/algorithm/search
 * @version 0.1
 * @date 2024-04-09
 *
 * @copyright Copyright (c) 2024
 *
 */

#include <algorithm>
#include <functional>
#include <iostream>
#include <vector>

int main()
{
    std::vector<int> testVector(1000000);
    std::cout << "size: " << testVector.size() << "\n";
    std::iota(testVector, , 0);
    std::vector vecNeedle(testVector.end() - 1000, testVector.end());

    auto it = std::search(testVector.begin(), testVector.end(),
                          std::boyer_moore_horspool_searcher(vecNeedle.begin(), vecNeedle.end()));

    if (it == testVector.end())
    {
        std::cout << "The pattern not found\n";
    }
}
