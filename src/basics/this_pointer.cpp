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
    // Default constructor
    Foo()
    {
        this->m_value = 0;
        std::cout << "Default constructor\n";
    }

    // Destructor
    ~Foo()
    {
        std::cout << "Destructor for object with value " << this->m_value << "\n";
    }

    // Copy constructor
    Foo(const Foo& obj) : m_value(obj.m_value)
    {
        std::cout << "Copy constructor (value: " << m_value << ")\n";
    }

    // Copy assignment operator
    Foo& operator=(const Foo& obj)
    {
        if (this != &obj)
        {
            std::cout << "Copy assignment (old value: " << m_value << ", new value: " << obj.m_value << ")\n";
            m_value = obj.m_value;
        }
        return *this;
    }

    // Move constructor
    Foo(Foo&& obj) noexcept
    {
        m_value = obj.m_value;
        obj.m_value = 0;  // Reset moved-from object
        std::cout << "Move constructor (value: " << m_value << ")\n";
    }

    // Move assignment operator
    Foo& operator=(Foo&& obj) noexcept
    {
        if (this != &obj)
        {
            std::cout << "Move assignment (old value: " << m_value << ", new value: " << obj.m_value << ")\n";
            m_value = obj.m_value;
            obj.m_value = 0;  // Reset moved-from object
        }
        return *this;
    }

    Foo getCopy()
    {
        std::cout << "getCopy() called\n";
        return *this;
    }

    Foo& getCopyAsReference()
    {
        std::cout << "getCopyAsReference() called\n";
        return *this;
    }

    Foo* getPointer()
    {
        std::cout << "getPointer() called\n";
        return this;
    }

    void increment()
    {
        this->m_value++;
        std::cout << "increment() - new value: " << this->m_value << "\n";
    }

    void printValue() const
    {
        std::cout << "Value: " << this->m_value << std::endl;
    }

private:
    int m_value = 0;
};

int main()
{
    std::cout << "=== Creating foo ===\n";
    Foo foo;
    foo.increment();   // Value becomes 1
    foo.printValue();  // Prints 1

    std::cout << "\n=== Creating foo_copy via getCopy() ===\n";
    auto foo_copy = foo.getCopy();  // This will call copy constructor
    foo_copy.increment();           // foo_copy becomes 2
    foo_copy.printValue();          // Prints 2

    std::cout << "\n=== Getting reference via getCopyAsReference() ===\n";
    auto& foo_copy_as_reference = foo.getCopyAsReference();  // Returns reference to foo
    foo_copy_as_reference.increment();                       // foo becomes 2
    foo_copy_as_reference.printValue();                      // Prints 2

    foo_copy_as_reference.increment();  // foo becomes 3

    std::cout << "\n=== Printing foo after modifications via reference ===\n";
    foo.printValue();  // Prints 3

    std::cout << "\n=== Getting pointer via getPointer() ===\n";
    auto foo_pointer = foo.getPointer();
    foo_pointer->increment();   // foo becomes 4
    foo_pointer->printValue();  // Prints 4

    foo_pointer->increment();  // foo becomes 5

    std::cout << "\n=== Printing foo after modifications via pointer ===\n";
    foo.printValue();  // Prints 5

    std::cout << "\n=== Addresses ===\n";
    std::cout << "foo address: " << &foo << "\nfoo_copy address: " << &foo_copy
              << "\ncopy_as_reference address: " << &foo_copy_as_reference << "\nfoo_pointer address: " << foo_pointer
              << "\n";

    std::cout << "\n=== End of program - destructors will be called ===\n";
    return 0;
}