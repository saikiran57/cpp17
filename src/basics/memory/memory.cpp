/**
 * @file memory.cpp
 * @author Saikiran Nadipilli
 * @brief
 * @version 0.1
 * @date 2025-01-31
 *
 * @copyright Copyright (c) 2025
 *
 */

#include <cassert>
#include <cstring>
#include <iostream>

struct S
{
    char m_c;   // 1 byte value
                // 3 bytes of padding bits (assuming alignof(float) == 4)
    float m_f;  // 4 bytes value (assuming sizeof(float) == 4)

    bool operator==(const S& arg) const  // value-based equality
    {
        return m_c == arg.m_c && m_f == arg.m_f;
    }
};

static void f()
{
    static_assert(sizeof(S) == 8);
    S s1 = {.m_c = 'a', .m_f = 3.14};
    S s2 = s1;
    assert(s1 == s2);
    reinterpret_cast<unsigned char*>(&s1)[2] = 'b';  // modify some padding bits
    assert(s1 == s2);                                // value did not change
    auto* s11 = reinterpret_cast<unsigned char*>(&s1);
    int const rc = std::memcmp(reinterpret_cast<unsigned char*>(&s1), reinterpret_cast<unsigned char*>(&s2), 8);

    if (rc < 0)
    {
        std::cout << " precedes ";
    }
    else if (rc > 0)
    {
        std::cout << " follows ";
    }
    else
    {
        std::cout << " compares equal to ";
    }
}

int main()
{
    f();
    return 0;
}