/**
 * @file this_pointer.cpp
 * @author Saikiran Nadipilli
 * @brief
 * @version 0.1
 * @date 2025-01-23
 *
 * @copyright Copyright (c) 2025
 *
 * @ref https://stackoverflow.com/questions/2750316/this-vs-this-in-c
 *
 */

#include <iostream>

class Foo
{
public:
    Foo()
    {
        this->value = 0;
    }

    Foo get_copy()
    {
        return *this;
    }

    Foo& get_copy_as_reference()
    {
        return *this;
    }

    Foo* get_pointer()
    {
        return this;
    }

    void increment()
    {
        this->value++;
    }

    void print_value()
    {
        std::cout << this->value << std::endl;
    }

private:
    int value;
};

int main()
{
    Foo foo;
    foo.increment();
    foo.print_value();

    foo.get_copy().increment();
    foo.print_value();

    foo.get_copy_as_reference().increment();
    foo.print_value();

    foo.get_pointer()->increment();
    foo.print_value();

    return 0;
}