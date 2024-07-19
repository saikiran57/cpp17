/**
 * @file static_cast.cpp
 * @author Saikiran Nadipilli
 * @brief 
 * @version 0.1
 * @date 2024-07-17
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#include <iostream>

int main()
{
    int a = 65;
    char b = 'C';

    // reinterpret cast can only be used in unrelated pointer types
    char* p = reinterpret_cast<char*>(&a);

    std::cout << "a:" << a << " b:" << b << "\n";
}