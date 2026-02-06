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

#include <iostream>

/**
 * @brief Crtp design
 *
 */

template <typename derived>
class crtp
{
private:
    /* data */

public:
    void do_something_base()
    {
        std::cout << "I am from base class\n";
        auto underlying = static_cast<derived*>(this);
        underlying->do_something();
    }

protected:
    crtp(/* args */) = default;
    ~crtp() = default;
};

class derived1 : public crtp<derived1>
{
public:
    void do_something()
    {
        std::cout << "I am doing something in derived 1\n";
    }
};

class derived2 : public crtp<derived2>
{
public:
    void do_something()
    {
        std::cout << "I am doing something in derived 2\n";
    }
};

template <typename T>
void something(T& base)
{
    base.do_something_base();
}

int main(int argc, char const* argv[])
{
    derived1 d1;
    derived2 d2;

    something(d1);
    something(d2);
    return 0;
}
