/**
 * @file copy.cpp
 * @author Saikiran Nadipilli
 * @brief
 * @version 0.1
 * @date 2024-06-21
 *
 * @copyright Copyright (c) 2024
 *
 */

#include <algorithm>
#include <iostream>
#include <iterator>
#include <vector>

void print(const std::string_view sv, std::vector<int> list)
{
    std::cout << sv << ": ";
    for (auto l : list)
    {
        std::cout << l << " ";
    }

    std::cout << "\n";
}

void testFunc()
{
    std::vector<int> v{1, 2, 0, -1, -2};
    std::vector<int> v2;
    // standard copy
    std::copy(v.begin(), v.end(), std::back_inserter(v2));
    print("standard copy", v2);

    // copy_n
    v2.clear();
    std::copy_n(v.begin(), 3, std::back_inserter(v2));
    print("copy n elements", v2);

    // copy_if
    std::vector<int> v3;
    std::copy_if(v.begin(), v.end(), std::back_inserter(v3), [](int x) {
        if (x % 2 == 0) return true;
        return false;
    });

    print("copy if", v3);

    // copy_backward
    v3.clear();
    v3.assign(10, -1);
    std::copy_backward(v.begin(), v.end(), v3.end());
    print("copy backward", v3);

    // copy print
    std::copy(v3.begin(), v3.end(), std::ostream_iterator<int>(std::cout, ", "));
}

int main()
{
    testFunc();
    return 0;
}
