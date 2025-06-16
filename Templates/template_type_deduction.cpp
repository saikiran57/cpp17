/**
 * @file template_type_deduction.cpp
 * @author Saikiran Nadipilli
 * @brief
 * @version 0.1
 * @date 2024-12-27
 *
 * @copyright Copyright (c) 2024
 *
 */

#include <iostream>
#include <string>

template <typename T>
static void func(T v)
{
    std::cout << v << '\n';
}

template <typename T>
static void func(T* v)
{
    std::cout << *v << '\n';
}

template <typename T>
static void func(const T* v)
{
    std::cout << *v << '\n';
}

int main()
{
    func(1);
    func("sss");
    func(1.33);

    std::string t = "s";
    func(&t);
    return 0;
}