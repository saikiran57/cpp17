/**
 * @file from_chars.cpp
 * @author Saikiran Nadipilli
 * @brief
 * @version 0.1
 * @date 2025-05-26
 *
 * @copyright Copyright (c) 2025
 *
 * https://medium.com/@simontoth/daily-bit-e-of-c-std-from-chars-9eb8d74514fc
 *
 * https://www.cppstories.com/2018/12/fromchars/
 *
 */

#include <charconv>  // support from_chars
#include <iostream>
#include <string_view>

/**
 * @brief convert string to integer using from_chars
 *
 * https://godbolt.org/z/bEa8YTE4x
 *
 * @return int
 */
template <typename T>
bool stringToNum(std::string_view str, T& num, std::chars_format format = std::chars_format::fixed)
{
    if constexpr (std::is_same_v<T, std::floating_point>)
    {
        auto [ptr, ec] = std::from_chars(str.begin(), str.end(), num, format);
    }
    else
    {
        auto [ptr, ec] = std::from_chars(str.begin(), str.end(), num);
    }

    if (ec == std::errc())
    {
        return true;
    }
    else if (ec == std::errc::invalid_argument)
    {
        std::cout << str << " is not a number\n";
    }
    else if (ec == std::errc::result_out_of_range)
    {
        std::cout << str << " is out of range\n";
    }
    return false;
}

int main()
{
    const std::string str{"12345678901234"};
    long long value = 0;
    auto [ptr, ec] = std::from_chars(str.data(), str.data() + str.size(), value);

    std::cout << value << "\n";

    std::string_view sv = "1235";
    int number = 0;
    if (stringToNum(sv, number))
    {
        std::cout << number << "\n";
    }

    std::string_view sv2 = "12345678901234";
    long long longNumber = 0;
    if (stringToNum(sv2, longNumber))
    {
        std::cout << "long long:" << longNumber << "\n";
    }

    std::string_view sv3 = "15.244";
    float floatVal = 0.0f;

    if (stringToNum(sv3, floatVal))
    {
        std::cout << "float val:" << floatVal << "\n";
    }

    std::string_view sv4 = "-6";
    int floatVal2 = 0;

    if (stringToNum(sv4, floatVal2))
    {
        std::cout << "float val2:" << floatVal2 << "\n";
    }

    // scientific notation
    std::string_view sv5 = "2.1e+5";
    long long scientificVal = 0;

    if (stringToNum(sv5, scientificVal))
    {
        std::cout << "scientificVal val2:" << scientificVal << "\n";
    }

    return 0;
}