/**
 * @file function_spec.cpp
 * @author Saikiran Nadipilli
 * @version 0.1
 * @date 2025-06-02
 *
 * @copyright Copyright (c) 2025
 *
 */

/**
 * @brief Function overloads vs function specializations
 *
 * http://www.gotw.ca/publications/mill17.htm
 *
 *
 */

#include <iostream>

template <class T>
void f(T)  // #1: overload for all types
{
    std::cout << "less specialized template\n";
}

template <>
void f(int*)  // #2: specialization of #1 for pointers to int
{
    std::cout << "Explicit specialized template\n";
}

template <class T>
void f(T*)  // #3: overload for all pointer types
{
    std::cout << "more specialized template\n";
}

int main()
{
    f(new int(1));  // calls #3, even though specialization of #1 would be a perfect match

    return 0;
}