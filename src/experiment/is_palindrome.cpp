/**
 * @file is_palindrome.cpp
 * @author Saikiran Nadipilli (saikirannadipilli@gmail.com)
 * @brief
 * @version 0.1
 * @date 2026-02-10
 *
 * @copyright Copyright (c) 2026
 *
 */

#include <iostream>
#include <string_view>

// constexpr alnum (no <cctype>)
constexpr bool is_alnum(char c)
{
    return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c >= '0' && c <= '9');
}

// constexpr lowercase
constexpr char lower(char c)
{
    return (c >= 'A' && c <= 'Z') ? (c - 'A' + 'a') : c;
}

constexpr bool is_palindrome(const std::string_view sv)
{
    std::size_t i = 0;
    std::size_t j = sv.size();

    if (j == 0) return true;
    --j;

    while (i < j)
    {
        // Skip punctuation / whitespace
        while (i < j && !is_alnum(sv[i]))
            ++i;
        while (i < j && !is_alnum(sv[j]))
            --j;

        if (lower(sv[i]) != lower(sv[j])) return false;

        ++i;
        --j;
    }

    return true;
}

int main()
{
    static_assert(is_palindrome("A man, a plan, a canal: Panama"));
    static_assert(is_palindrome("Was it a car or a cat I saw?"));
    static_assert(is_palindrome("No 'x' in Nixon"));
    static_assert(!is_palindrome("hello"));

    std::cout << std::boolalpha;
    std::cout << is_palindrome("A man, a plan, a canal: Panama") << "\n";
    std::cout << is_palindrome("No 'x' in Nixon") << "\n";
    std::cout << is_palindrome("hello") << "\n";
}