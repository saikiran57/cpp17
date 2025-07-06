/**
 * @file placement_new.cpp
 * @author Saikiran Nadipilli (saikirannadipilli@gmail.com)
 * @brief
 * @version 0.1
 * @date 2025-06-23
 *
 * @copyright Copyright (c) 2025
 *
 */

// https
//     :  // selfboot.cn/en/2024/05/10/c++_object_model/
//        https
//     :  // www.geeksforgeeks.org/dsa/stack-vs-heap-memory-allocation/

//  #include "../../common/complex_widget.hpp"

//  int main()
//  {
//     // buffer on stack
//     unsigned char buf[sizeof(complex_widget)];

//     auto widget = new(buf) complex_widget(10);

//     widget->~complex_widget();

//     return 0;
//  }

// CPP program to illustrate
// use of operator new
#include <iostream>
#include <string>

using namespace std;

// Global operator new overload
void* operator new(size_t size)
{
    std::cout << "Global operator new is called with size: " << size << "\n";

    auto p = malloc(size);
    if (p == nullptr)
    {
        throw std::bad_alloc();
    }

    return p;
}

void operator delete(void* p)
{
    std::cout << "Global operator delete is called \n";

    if (p)
    {
        free(p);
    }
}

class car
{
    string name;
    int num;
    int* data;

public:
    car(string a, int n)
    {
        cout << "Constructor called" << endl;
        this->name = a;
        this->num = n;
        data = new int(n);
    }
    ~car()
    {
        if (data)
        {
            cout << "destructor called" << std::endl;
            delete data;
        }
    }

    void display()
    {
        cout << "Name: " << name << endl;
        cout << "Num: " << num << endl;
    }

    // void *operator new(size_t size)
    // {
    //     cout << "new operator overloaded" << endl;
    //     void *p = malloc(size);
    //     return p;
    // }

    // void operator delete(void *ptr)
    // {
    //     cout << "delete operator overloaded" << endl;
    //     free(ptr);
    // }
};

#include <cstdint>
#include <cstring>
#include <string>

int main()
{
    int* i = new int;  // This will call the overloaded global operator new
    delete i;          // This will call the overloaded global operator delete

    double* d = new double[5];  // This will also call the overloaded global operator new (for array allocation)
    delete[] d;                 // This will also call the overloaded global operator delete (for array deallocation)

    static uint8_t buff[sizeof(int)];

    // placement new
    int* q = new (buff) int(10);

    uint32_t value;

    // Copy the bytes into the integer variable
    std::memcpy(&value, buff, sizeof(value));

    std::cout << "buff value: " << value << " buff contains:" << &buff << "\n";
    std::cout << "q value: " << *q << " q contains:" << q << "\n";

    // stack allocation
    // car c("hyundai", 100);

    // car *p = new car("HYUNDAI", 2012);
    // delete p;

    // unsigned char buff[sizeof(car)];
    // std::cout << "size of car: " << sizeof(car) << "\n";
    // auto p = new(buff) car("HYUNDAI", 2012);
    // p->display();
    // p->~car();
}