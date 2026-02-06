/**
 * @file crtp.cpp
 * @author Saikiran Nadipilli (saikirannadipilli@gmail.com)
 * @brief
 * @version 0.1
 * @date 2026-02-04
 *
 * @copyright Copyright (c) 2026
 *
 */

#include "crtp.hpp"
#include <iostream>
#include <type_traits>

/**
 * @brief Crtp design with compile-time type checking
 *
 */

template <typename derived>
class crtp : public crtp_base<derived>
{
private:
    /* data */

protected:
    // Protected constructor to enforce CRTP pattern
    // Only allows instantiation through proper derived class
    crtp() = default;
    ~crtp() = default;

public:
    void do_something()
    {
        std::cout << "I am from base class\n";
        // auto underlying = static_cast<derived*>(this);
        // underlying->do_something();
        this->impl().do_something();  // correct
        // crtp_base<derived>::impl().do_something();  // correct
    }
};

class derived1 : public crtp<derived1>
{
public:
    void do_something() const noexcept
    {
        std::cout << "I am doing something in derived 1\n";
    }
};

class derived2 : public crtp<derived2>
{
public:
    void do_something() const noexcept
    {
        std::cout << "I am doing something in derived 2\n";
    }
};

class derived3 : public crtp<derived3>
{
public:
    void do_something() const noexcept
    {
        std::cout << "I am doing something in derived3\n";
    }
};

class derived4 : public crtp<derived4>
{
public:
    void do_something() const noexcept
    {
        std::cout << "I am doing something in derived4\n";
    }
};

template <typename T>
void something(crtp<T>& base)
{
    base.do_something();
}

int main(int argc, char const* argv[])
{
    derived1 d1;
    derived2 d2;
    derived3 d3;

    something(d1);
    something(d2);
    something(d3);

    return 0;
}
