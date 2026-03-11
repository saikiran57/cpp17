/**
 * @file reference_problem.cpp
 * @author Saikiran Nadipilli (saikirannadipilli@gmail.com)
 * @brief
 * @version 0.1
 * @date 2026-03-03
 *
 * @copyright Copyright (c) 2026
 *
 * @ref: https://manski.net/articles/cpp/references-and-inheritance/reference_problem.cpp
 */

#include <iostream>
#include <string>

using namespace std;

class BaseClass
{
public:
    virtual ~BaseClass() = default;

    virtual void write() const
    {
        printf("In base class\n");
    }
    virtual void incr() = 0;
};

using BaseClassPointer = BaseClass*;

class ChildClass : public BaseClass
{
public:
    void write() const override
    {
        printf("In child class\n");
    }

    void incr() override
    {
        ++value;
    }

    int value = 0;
};

using ChildClassPointer = ChildClass*;

BaseClass* g_somePointer = new ChildClass();
// ChildClass* g_somePointer = new ChildClass();

const BaseClassPointer& getReference()
{
    const BaseClassPointer& val = g_somePointer;
    val->incr();

    return val;
}

int main()
{
    BaseClassPointer child = getReference();

    child->write();

    return 0;
}