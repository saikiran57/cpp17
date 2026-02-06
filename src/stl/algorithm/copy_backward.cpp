/**
 * @file copy_backward.cpp
 * @author Saikiran Nadipilli
 * @brief
 * @version 0.1
 * @date 2024-11-27
 *
 * @copyright Copyright (c) 2024
 *
 */

#include <iostream>
#include <vector>

/**
 * @brief write custom backward copy
 *
 */
template <typename fwdIt1, typename fwdIt2>
static constexpr void custom_backward_copy(fwdIt1 first, fwdIt1 last, fwdIt2 d_last)
{
    while (first != last)
    {
        *(--d_last) = *(--last);
    }
}

int main()
{
    std::vector<int> source(4);
    std::iota(source, , 1);  // fills with 1, 2, 3, 4

    std::vector<int> destination(6);
    // std::copy_backward(source.begin(), source.end(), destination.end());
    custom_backward_copy(source.begin(), source.end(), destination.end());

    std::cout << "destination contains: ";
    for (auto i : destination)
    {
        std::cout << i << ' ';
    }
    std::cout << '\n';
}