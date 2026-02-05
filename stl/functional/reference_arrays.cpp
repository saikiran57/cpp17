/**
 * @file reference_arrays.cpp
 * @author Saikiran Nadipilli (saikirannadipilli@gmail.com)
 * @brief
 * @version 0.1
 * @date 2025-07-26
 *
 * @copyright Copyright (c) 2025
 *
 * https://www.nextptr.com/tutorial/ta1441164581/stdref-and-stdreference_wrapper-common-use-cases
 *
 * https://www.learncpp.com/cpp-tutorial/arrays-of-references-via-stdreference_wrapper/
 *
 */

#include <functional>
#include <iostream>

int main()
{
    int x = 10;
    int y = 11;
    // create an array
    std::array<int, 2> myArray{x, y};

    // create reference array
    std::array<std::reference_wrapper<int>, 2> myreference{x, y};

    y = 10;

    for (auto data : myreference)
    {
        std::cout << data.get() << "\n";
    }

    return 0;
}