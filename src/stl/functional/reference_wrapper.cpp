/**
 * @file reference_wrapper.cpp
 * @author Saikiran Nadipilli
 * @brief
 * @version 0.1
 * @date 2024-05-20
 *
 * @copyright Copyright (c) 2024
 *
 */

// https://www.nextptr.com/tutorial/ta1441164581/stdref-and-stdreference_wrapper-common-use-cases

#include <algorithm>
#include <functional>
#include <iostream>
#include <list>
#include <numeric>
#include <random>
#include <vector>

template <typename T>
void println(auto const rem, T v)
{
    std::cout << rem;
    for (auto const& e : v)
        std::cout << e << ' ';
    std::cout << '\n';
}

int main()
{
    std::list<int> l(10);
    std::iota(l.begin(), l.end(), -4);

    // can't use shuffle on a list (requires random access), but can use it on a vector
    std::vector<std::reference_wrapper<int>> v(l.begin(), l.end());

    std::shuffle(v.begin(), v.end(), std::mt19937{std::random_device{}()});

    println("Contents of the list: ", l);
    println("Contents of the list, as seen through a shuffled vector: ", v);

    std::cout << "Doubling the values in the initial list...\n";
    std::for_each(l.begin(), l.end(), [](int& i) {
        i *= 2;
    });

    println("Contents of the list, as seen through a shuffled vector: ", v);
}
