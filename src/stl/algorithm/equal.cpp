/**
 * @file equal.cpp
 * @author Saikiran Nadipilli (saikirannadipilli@gmail.com)
 * @brief
 * @version 0.1
 * @date 2026-02-10
 *
 * @ref name "https://en.cppreference.com/w/cpp/algorithm/equal.html"
 * @copyright Copyright (c) 2026
 *
 */

#include <algorithm>
#include <iomanip>
#include <iostream>
#include <string_view>

// compile time palindrome check with equal operator
constexpr bool is_palindrome(std::string_view s)
{
    return std::equal(s.cbegin(), s.cbegin() + s.size() / 2, s.crbegin());
}

void test(std::string_view s)
{
    std::cout << std::quoted(s) << (is_palindrome(s) ? " is" : " is not") << " a palindrome\n";
}

int main()
{
    test("radar");
    test("hello");
}