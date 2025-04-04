/**
 * @file vector.cpp
 * @author Saikiran Nadipilli
 * @version 0.1
 * @date 2024-04-09
 *
 * @copyright Copyright (c) 2024
 *
 */

/**
 * @brief https://en.cppreference.com/w/cpp/container/vector/vector
 *
 * https://hackingcpp.com/cpp/std/vector.html
 *
 */

#include <iostream>
#include <numeric>
#include <vector>

template <typename T>
static std::ostream& operator<<(std::ostream& s, const std::vector<T> vec)
{
    s.put('{');
    char comma[]{'\0', ' ', '\0'};
    for (const auto& e : vec)
    {
        s << comma << e, comma[0] = ',';
    }
    return s << "}\n";
}

template <class ForwardIt, class T>
static void iotat(ForwardIt first, ForwardIt last, T value)
{
    for (; first != last; ++first, ++value)
    {
        *first = value;
    }
}

int main()
{
    // construct a new vector

    std::vector<int> vec1{1, 2, 3, 4, 5, 6};  // create a vector using initializer_list
    std::vector<int> const vec2(vec1.begin() + 3, vec1.end());
    std::vector<int> vec3(10);           // create 10 elements holding 0
    std::vector<int> const vec4{100};    // create 1 element holding 100
    std::vector<int> const vec5(10, 3);  // create 100 elements holding 3

    std::vector<int> const deepCopyVec(vec1);  // Deep copy from vec1

    std::vector const vec6{"a", "bb", "ccc"};  // auto type deduction since c++17

    std::iota(vec3.begin(), vec3.end(), 0);  // increase vector element by 1

    std::vector<std::vector<int>::iterator> vec7(vec3.size());
    std::iota(vec7.begin(), vec7.end(), vec3.begin());

    std::cout << "vec1: " << vec1 << "vec2: " << vec2 << "vec3: " << vec3;

    std::cout << "Contents of l, viewed via shuffled v:\n";
    for (auto const i : vec7)
    {
        std::cout << " " << *i << ' ';
    }

    return 0;
}
