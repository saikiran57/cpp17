/**
 * @file basics.cpp
 * @author Saikiran Nadipilli
 * @brief
 * @version 0.1
 * @date 2024-07-19
 *
 * @copyright Copyright (c) 2024
 *
 */

#include <iostream>

template <typename T>
static void sum(T a, T b)
{
    T c = a + b;
    std::cout << "Sum:" << c << "\n";
}

template <typename T>  // primary template
void f(const T x)
{
    std::cout << x << std::endl;
}

template <typename T>  //
void f(const T* x)
{
    std::cout << *x << std::endl;
}

// Explicit specialization of f with 'std::string' with the
// template argument explicitly specified:
template <>
void f<std::string>(const std::string x)
{
    std::cout << x << std::endl;
}

// Explicit specialization of f with 'int' with the
// template argument deduced:
template <>
void f(const int x)
{
    std::cout << x << std::endl;
}

int main()
{
    sum(1, 3);
    std::string data = "mystring";
    f(data);
    f(123);
}
