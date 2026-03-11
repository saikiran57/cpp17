/**
 * @file reference_basics.cpp
 * @author Saikiran Nadipilli (saikirannadipilli@gmail.com)
 * @brief
 * @version 0.1
 * @date 2026-03-02
 *
 * @copyright Copyright (c) 2026
 *
 */

/**
 * @brief reference_wrapper is class template that wraps a reference in a copyable and assignable object.
 *
 * https://www.geeksforgeeks.org/cpp/passing-reference-to-a-pointer-in-c/
 *
 */

#include <algorithm>
#include <array>
#include <iostream>
#include <numeric>
#include <ranges>
#include <vector>

#include "../../../include/common/complex_widget.hpp"

template <typename T>
void change(T a)
{
    ++a;
}

int global_Var = 42;

// function to change pointer value
/**
 * @brief
 * If a pointer is passed to a function as a parameter and tried to be modified then the changes
 * made to the pointer does not reflects back outside that function.
 * This is because only a copy of the pointer is passed to the function.
 * It can be said that "pass by pointer" is passing a pointer by value. In most cases,
 * this does not present a problem. But the problem comes when you modify the pointer inside the function.
 * Instead of modifying the variable, you are only modifying a copy of the pointer and the original pointer remains
 * unmodified
 *
 * @param pp
 */
void changePointerValue(int* pp)
{
    pp = &global_Var;
}

// function to change pointer to pointer value
void changePointerValue(int** ptr_ptr)
{
    *ptr_ptr = &global_Var;
}

// function to change Reference to pointer value
void changeReferenceValue(int*& pp)
{
    pp = &global_Var;
}

using namespace std;

void passing_reference_test()
{
    {
        // Passing pointer to a function
        int var = 23;
        int* ptr_to_var = &var;

        cout << "Passing Pointer to function:" << endl;

        cout << "Before :" << *ptr_to_var << endl;  // display 23

        changePointerValue(ptr_to_var);

        cout << "After :" << *ptr_to_var << endl;  // display 23
    }

    {
        // Passing "pointer to a pointer" as a parameter to function
        int var = 23;
        int* pointer_to_var = &var;

        cout << "Passing a pointer to a pointer to function " << endl;

        cout << "Before :" << *pointer_to_var << endl;  // display 23

        changePointerValue(&pointer_to_var);

        cout << "After :" << *pointer_to_var << endl;  // display 42
    }

    {
        // pass a "Reference to a pointer" to a function:
        int var = 23;
        int* ptr_to_var = &var;

        cout << "Passing a Reference to a pointer to function" << endl;

        cout << "Before :" << *ptr_to_var << endl;  // display 23

        changeReferenceValue(ptr_to_var);

        cout << "After :" << *ptr_to_var << endl;  // display 42
    }
}

void foo()
{
    int x = 10;
    change(&x);  // pass by pointer change(int* a)
    std::cout << "x: " << x << "\n";

    int& xref = x;
    change(xref);  // Passed by value it will assume int change(int a)
    // x is still 10
    std::cout << x << "\n";  // 10

    // Be explicit to pass by reference
    change<int&>(x);
    // x is 11 now
    std::cout << x << "\n";  // 11

    // Or use std::ref
    change(std::ref(x));  // Passed by reference
    // x is 12 now
    std::cout << x << "\n";  // 12
}

void array_test()
{
    // std::vector v1{1,2,3,4,5};
    // std::vector v2{6,7,8,9,10};

    // std::array a1{v1, v2};
    // std::vector<std::reference_wrapper<int>> v3;
    // v3.reserve(v1.size() + v2.size());

    // v3.insert(v3.end(), v1.begin(), v1.end());
    // v3.insert(v3.end(), v2.begin(), v2.end());

    // for(auto value : v3)
    // {
    //     std::cout << value << "\n";
    // }

    std::vector<complex_widget> v1;
    std::vector<complex_widget> v2;
    v1.reserve(5);
    v2.reserve(5);

    for (int i = 0; i < 5; ++i)
    {
        v1.emplace_back(i);
        v2.emplace_back(i + 5);
    }

    std::vector<std::reference_wrapper<complex_widget>> v3;
    v3.reserve(v1.size() + v2.size());
    v3.insert(v3.end(), v1.begin(), v1.end());
    v3.insert(v3.end(), v2.begin(), v2.end());

    std::cout << "V1 at 0:" << v1.front().get_value() << "\n";
    std::cout << "V2 at 0:" << v2.front().get_value() << "\n";
    std::cout << "V3 at 0:" << v3.front().get().get_value() << "\n";

    std::puts("------------- After update ----------- \n");
    complex_widget cw(1000);
    v1[0] = cw;

    std::cout << "V1 at 0:" << v1.front().get_value() << "\n";
    std::cout << "V2 at 0:" << v2.front().get_value() << "\n";
    std::cout << "V3 at 0:" << v3.front().get().get_value() << "\n";
}

int main()
{
    passing_reference_test();

    foo();

    array_test();

    /*
    1.  A reference cannot rebind to another object.
        Therefore, assigning a reference to another does not assign the reference itself;
    2.  Declaring a reference to a reference, an array of references, and a pointer to a reference is forbidden in C++.
    3.  Reference types do not meet the Erasable requirement of STL container elements.
        Therefore, we cannot have a container (e.g., vector or list) of reference elements.
    4.  C++ references are not null.
    5.  As references cannot rebind, having a reference class member is a pain in the neck because a reference member
    makes a class non-assignable — the default copy-assignment operator is deleted. Move-semantics does not make sense
    with a reference member altogether
    */

    int X = 10;
    int& refX = X;
    // can we print address of refX?
    std::cout << "X address: " << &X << " refX address: " << &refX << "\n";

    {
        int Y = 20;
        refX = Y;
        int& refY = Y;
        ++refX;

        std::cout << "X value: " << X << " Y Value: " << Y << " refX: " << refX << "\n";
    }

    {
        // a reference cannot rebind to another object.
        // Therefore, assigning a reference to another does not assign the reference itself; it assigns the object

        int x = 10, y = 20;
        int &xref = x, &yref = y;

        xref = yref;
        // xref still refers x, which is 20 now.
        ++x;

        std::cout << "X value: " << x << " Y Value: " << y << " xref: " << xref << " yref: " << yref << "\n";
    }

    {
        // reference types do not meet the Erasable requirement of STL container elements.
        // Therefore, we cannot have a container (e.g., vector or list) of reference elements:
        // std::vector<int&> v; //Error
    }

    return 0;
}