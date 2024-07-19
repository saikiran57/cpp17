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
void sum(T a, T b)
{
    T c = a + b;
    std::cout << "Sum:" << c << "\n";
}

int main()
{
    sum(1, 3);
}
