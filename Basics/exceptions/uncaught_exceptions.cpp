/**
 * @file uncaught_exceptions.cpp
 * @author Saikiran Nadipilli (saikirannadipilli@gmail.com)
 * @brief
 * @version 0.1
 * @date 2026-02-05
 *
 * @copyright Copyright (c) 2026
 *
 * @ref: https://en.cppreference.com/w/cpp/error/uncaught_exception.html
 *
 */

#include <exception>
#include <iostream>
#include <stdexcept>

struct Foo
{
    char id{'?'};
    int count = std::uncaught_exceptions();

    ~Foo()
    {
        count == std::uncaught_exceptions() ? std::cout << id << ".~Foo() called normally\n"
                                            : std::cout << id << ".~Foo() called during stack unwinding\n";
    }
};

int main()
{
    Foo f{'f'};

    try
    {
        Foo g{'g'};
        std::cout << "Exception thrown\n";
        throw std::runtime_error("test exception");
    }
    catch (const std::exception& e)
    {
        std::cout << "Exception caught: " << e.what() << '\n';
    }
}