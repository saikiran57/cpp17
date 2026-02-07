/**
 * @file function_overloading.cpp
 * @author Saikiran Nadipilli (saikirannadipilli@gmail.com)
 * @brief
 * @version 0.1
 * @date 2026-02-06
 *
 * @copyright Copyright (c) 2026
 *
 */

#include <iostream>

int func(int* a)
{
    std::cout << "non const *a\n";
    *a = 1;
    return *a;
}

const int func(const int* a)
{
    std::cout << "const *a\n";
    return *a;
}

int main(int argc, char const* argv[])
{
    int a = 10;
    const int b = 10;
    func(&a);
    func(&b);
    return 0;
}
