/**
 * @file top_list.cpp
 * @author Saikiran Nadipilli
 * @brief
 * @version 0.1
 * @date 2024-11-22
 *
 * @copyright Copyright (c) 2024
 *
 */

#include <algorithm>
#include <array>
#include <iostream>
#include <map>
#include <numeric>
#include <queue>
#include <stack>
#include <vector>

void print(const std::vector<int>& v, const std::string& name)
{
    std::cout << "\n " << name;
    for (auto&& i : v)
    {
        std::cout << " " << i;
    }
}

int main()
{
    std::vector<int> v1{1, 2, 3, 4, 5, 6, 9, 8, 7};

    print(v1, "original v1:");

    // sort a given list
    // sort	sort(first, last)	Sorting elements in ascending order	sort(myVector.begin(), myVector.end());
    // Time Complexity: O(N log N) Space Complexity: O(log N)
    std::sort(v1.begin(), v1.end());
    print(v1, "sort in ascending order");

    // sort descending order
    std::sort(v1.begin(), v1.end(), std::greater<>{});
    print(v1, "sort in descending order");

    // find Searching for a specific value
    // Time Complexity: O(N) Space Complexity: O(1)
    auto targetValue = 4;
    auto result = std::find(v1.begin(), v1.end(), targetValue);
    result == std::end(v1) ? std::cout << "\n not found \n" : std::cout << "\n found \n";

    // accumulate Summing up the elements in a range
    // Time Complexity: O(N) Space Complexity: O(1)
    auto sum = std::accumulate(v1.begin(), v1.end(), 0);
    std::cout << "sum: " << sum << "\n";

    auto product = std::accumulate(v1.begin(), v1.end(), 1, std::multiplies<int>{});
    std::cout << "product: " << product << "\n";

    // transform Applying a unary operation to each element
    // Time Complexity: O(N) Space Complexity: O(N)
    std::transform(v1.cbegin(), v1.cend(), v1.begin(), [](int a) {
        a += 2;
        return a;
    });
    print(v1, "transform");

    std::vector<int> output(v1.size(), 0);
    std::transform(v1.cbegin(), v1.cend(), v1.cbegin(), output.begin(), std::plus<>{});
    print(output, "transform binary operation");

    // transform_reduce with two ranges
    // first it transform the given range and it will reduce
    // inner product
    auto innerProduct =
        std::transform_reduce(v1.cbegin(), v1.cend(), v1.cbegin(), 0, std::plus<>{}, std::multiplies<>{});
    std::cout << "\n Inner product: " << innerProduct << "\n";

    // transform_reduce with one range
    // we can use std::execution::par for parallel execution
    auto innerProduct2 = std::transform_reduce(v1.cbegin(), v1.cend(), 0, std::plus<>{}, [](int a) {
        return a * a;
    });
    std::cout << "\n Inner product2: " << innerProduct2 << "\n";

    // Minimum/maximum operations
    // max_element returns the largest element in a range
    auto max_elementItr1 = std::max_element(v1.cbegin(), v1.cend());
    std::cout << "Max element found at index " << std::distance(v1.cbegin(), max_elementItr1) << " has value "
              << *max_elementItr1 << '\n';

    std::vector strList{"abc", "def", "ghijk"};
    auto max_elementItr2 = std::max_element(strList.cbegin(), strList.cend());
    std::cout << "Max element found at index " << std::distance(strList.cbegin(), max_elementItr2) << " has value "
              << *max_elementItr2 << '\n';

    // min_element Finds the smallest element in the range [first, last)
    auto min_elementItr = std::min_element(v1.begin(), v1.end());
    std::cout << "min element has value " << *min_elementItr << " and index ["
              << std::distance(v1.begin(), min_elementItr) << "]\n";

    // minmax returns the smaller and larger of two elements
    // don't pass temporary values
    int n = 10000;
    int m = 100;
    auto [mm, xx] = std::minmax(n, m);
    std::cout << mm << ": " << xx << "\n";

    // std::minmax_element
    const auto [min, max] = std::minmax_element(std::begin(v1), std::end(v1));
    std::cout << "min = " << *min << ", max = " << *max << '\n';
}