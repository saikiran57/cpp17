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
        this->m_value = 0;
    }

    Foo getCopy()
    {
        return *this;
    }

    Foo& getCopyAsReference()
    {
        return *this;
    }

    Foo* getPointer()
    {
        return this;
    }

    void increment()
    {
        this->m_value++;
    }

    void printValue() const
    {
        std::cout << this->m_value << std::endl;
    }

private:
    int m_value;
};

int main()
{
    Foo foo;
    foo.increment();
    foo.printValue();

    foo.getCopy().increment();
    foo.printValue();

    foo.getCopyAsReference().increment();
    foo.printValue();

    foo.getPointer()->increment();
    foo.printValue();

    return 0;
}