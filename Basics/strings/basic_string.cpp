/**
 * @file basic_string.cpp
 * @author Saikiran Nadipilli
 * @brief
 * @version 0.1
 * @date 2025-04-13
 *
 * @copyright Copyright (c) 2025
 *
 */

#include <cassert>
#include <iomanip>
#include <iostream>
#include <string>

int main()
{
    // empty string
    std::string s1;
    assert(s1.empty() && (s1.length() == 0 && s1.size() == 0));
    std::cout << "s1 capacity:" << s1.capacity() << "\n";

    // string with count and char
    std::string s2(4, '+');
    std::cout << std::quoted(s2) << std::endl;

    std::string s3;
    s3.reserve(37);
    std::cout << "s3 capacity:" << s3.capacity() << "\n";
    s3 = "abcddddddddddddddddddddddddddddddddd";
    std::cout << "s3 capacity:" << s3.capacity() << "\n";

    std::string s = "abcd";
    auto rs = std::string(s.rbegin(), s.rend());
    std::cout << "s:" << s << " rs: " << rs << std::endl;
    return 0;
}