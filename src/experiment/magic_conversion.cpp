/**
 * @file magic_conversion.cpp
 * @author Saikiran Nadipilli
 * @brief
 * @version 0.1
 * @date 2025-07-21
 *
 * @copyright Copyright (c) 2025
 *
 * @ref https://belanyi.fr/2021/10/01/magic-conversions-in-c-/
 *
 */

#include <iostream>

class ToArray
{
    std::string_view s_;

public:
    ToArray(std::string_view s) : s_(s) {}

    template <size_t N>
    operator std::array<char, N>() const
    {
        std::array<char, N> ret;
        std::copy(s_.begin(), s_.end(), ret.begin());
        return ret;
    }
};

ToArray to_array(std::string_view s)
{
    return ToArray{s};
}

int main()
{
    std::string_view str1{"abc"};
    auto val = to_array(str1);
    return 0;
}