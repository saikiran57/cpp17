/**
 * @file final.cpp
 * @author Saikiran Nadipilli (saikirannadipilli@gmail.com)
 * @brief
 * @version 0.1
 * @date 2026-02-05
 *
 * @copyright Copyright (c) 2026
 *
 */

/**
 * @brief final specifier was introduced in c++11 and it has two main purpose
 *
 * prevent inheritance if it used in class level ex: class Test final
 *
 * prevent function override when used with virtual ex: virtual test() final
 *
 * It has another important feature called dervitualization meaning that it will help
 *
 * compiler to optimize the code by may be removing vtable but its upto compiler to decide.
 *
 * https://johnfarrier.com/the-definitive-guide-to-the-c-final-keyword/
 *
 */

#include <iostream>

class Base final
{
public:
    virtual void process()
    {  // 'final' helps compiler optimize
        std::cout << "Processing in Base\n";
    }
};

void execute(Base& obj)
{
    obj.process();  // Compiler may optimize this into a direct call
}

int main()
{
    Base obj;
    execute(obj);
    return 0;
}