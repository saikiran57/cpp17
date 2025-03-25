/**
 * @file alignment.cpp
 * @author Saikiran Nadipilli
 * @brief
 * @version 0.1
 * @date 2025-01-27
 *
 * @copyright Copyright (c) 2025
 *
 */

/**
 * @brief https://en.cppreference.com/w/cpp/language/object#Alignment
 *
 */

#include <iostream>

// objects of type S can be allocated at any address
// because both S.a and S.b can be allocated at any address
struct S
{
    char m_a;  // size: 1, alignment: 1
    char m_b;  // size: 1, alignment: 1
};  // size: 2, alignment: 1

// objects of type X must be allocated at 4-byte boundaries
// because X.n must be allocated at 4-byte boundaries
// because int's alignment requirement is (usually) 4
struct X
{
    int m_n;   // size: 4, alignment: 4
    char m_c;  // size: 1, alignment: 1
    // three bytes of padding bits
};  // size: 8, alignment: 4

struct B
{
    char m_mChar;      // size: 1
    double m_mDouble;  // size: 8
    int m_mInt;        // size: 4
};

struct C
{
    double m_mDouble;  // size: 8
    int m_mInt;        // size: 4
    char m_mChar;      // size: 1
};

int main()
{
    std::cout << "alignof(S) = " << alignof(S) << '\n'
              << "sizeof(S)  = " << sizeof(S) << '\n'
              << "alignof(X) = " << alignof(X) << '\n'
              << "sizeof(X)  = " << sizeof(X) << '\n'
              << "alignof(B) = " << alignof(B) << '\n'
              << "sizeof(B)  = " << sizeof(B) << '\n'
              << "alignof(C) = " << alignof(C) << '\n'
              << "sizeof(C)  = " << sizeof(C) << '\n';
}