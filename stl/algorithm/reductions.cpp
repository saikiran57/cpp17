/**
 * @file reductions.cpp
 * @author Saikiran Nadipilli
 * @brief
 * @version 0.1
 * @date 2024-05-19
 *
 * @copyright Copyright (c) 2024
 *
 */

/**
 * https://hackingcpp.com/cpp/std/algorithms/numeric.html#reduce
 */

#include <algorithm>
#include <execution>
#include <iostream>
#include <numeric>
#include <vector>

int main()
{
    std::vector<uint32_t> vec(10);
    std::iota(vec.begin(), vec.end(), 0);

    // sum of all indicies
    auto sum = std::reduce(vec.begin(), vec.end());  // v0+v1+v2....+vn = sum

    auto sum1 = std::reduce(vec.begin(), vec.end(), 100);  // 100+v0+v1+v2....+vn = sum

    auto sum2 = std::reduce(vec.begin(), vec.end(), 100, [](int x, int y) {
        return x + y;
    });  // 100+v0+v1+v2....+vn = sum

    std::vector<double> w{2.0, 1.5, 3.0, 1.5};
    auto product = std::reduce(w.begin(), w.end(), 1.0, std::multiplies<>{});  // 1.0*2.0*1.5*3.0*1.5=product

    // execute parallel sum
    auto psum = std::reduce(std::execution::par, vec.begin(), vec.end());

    std::cout << "sum :" << sum << "\n";
    std::cout << "sum1 :" << sum1 << "\n";
    std::cout << "sum2 :" << sum2 << "\n";
    std::cout << "product :" << product << "\n";
    std::cout << "psum :" << psum << "\n";
}
