// /**
//  * @file class_size.cpp
//  * @author Saikiran Nadipilli (saikirannadipilli@gmail.com)
//  * @brief
//  * @version 0.1
//  * @date 2026-02-13
//  *
//  * @copyright Copyright (c) 2026
//  *
//  */

// //  #include <iostream>

// //  class A{
// //     public:
// //     int x;
// //     virtual void value(){
// //     }
// //  };

// //  class B : public A{
// //     public:
// //     int y;
// //  };

// //  int main(int argc, char const *argv[])
// //  {

// //     void *p;

// //     std::cout << "size of pointer: " << sizeof(p) << "\n";

// //     // Class A size
// //     A a;
// //     std::cout << "Class A size: " << sizeof(a) << "\n";

// //     // class B size
// //     B b;
// //     std::cout << "Class B size: " << sizeof(b) << "\n";

// //     return 0;
// //  }

// #include <iostream>

// struct Example {
//     char c;    // 1 byte
//     int i;     // 4 bytes
//     short s;   // 2 bytes
// };

// class Base {
// public:
//     int a;
//     char c;
// };

// class Derived : public Base {
// public:
//     char s;
// };

// int main() {
//     std::cout << "int size: " << sizeof(int) << "\n";
//     std::cout << "short size: " << sizeof(short) << "\n";
//     std::cout << "char size: " << sizeof(char) << "\n";

//     std::cout << "Example size: " << sizeof(Example) << "\n";
//     std::cout << "Base size: " << sizeof(Base) << "\n";
//     std::cout << "Derived size: " << sizeof(Derived) << "\n";
//     return 0;
// }

#include <iostream>
using namespace std;

class Basic
{
public:
    int a;
    double b;
};

int main()
{
    Basic temp;
    temp.a = 10;
    return 0;
}