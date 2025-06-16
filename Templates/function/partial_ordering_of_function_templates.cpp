/**
 * @file partial_ordering_of_function_templates.cpp
 * @author Saikiran Nadipilli
 * @brief
 * @version 0.1
 * @date 2025-05-31
 *
 * @copyright Copyright (c) 2025
 *
 * Partial Template Specialization
 * https://www.geeksforgeeks.org/partial-template-specialization-in-cpp/
 */

#include <iostream>

template <typename T>
void f(T)
{
    std::cout << "less specialized template\n";
}

// template<class T> void g(T);  //(1)
// template<class T> void g(T&); //(2)

void g(int)
{
    std::cout << "pass by value\n";
}
// void g(int*)
// {
//     std::cout << "pass by pointer\n";
// }
void g(const int*)
{
    std::cout << "pass by const pointer\n";
}

int main()
{
    int i = 10;
    const int j = 20;
    int* pi = &i;
    const int* cpi = &i;

    f(i);
    f(j);
    f(pi);
    f(cpi);

    g(cpi);
    g(pi);

    return 0;
}