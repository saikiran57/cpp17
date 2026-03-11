/**
 * @file pointer_cast.cpp
 * @author Saikiran Nadipilli (saikirannadipilli@gmail.com)
 * @brief
 * @version 0.1
 * @date 2026-02-23
 *
 * @copyright Copyright (c) 2026
 *
 */

#include <iostream>
#include <memory>

class Base
{
public:
    Base() = default;
    virtual ~Base() = default;
    virtual void f() const noexcept
    {
        std::cout << "I am Base f() \n";
    }
};

class Derived : public Base
{
public:
    ~Derived() = default;
    void f() const noexcept override
    {
        std::cout << "I am Derived f() \n";
    }
    void g() noexcept
    {
        std::cout << "I am Derived g()\n";
    }
};

void raw_pointer_casting()
{
    Base* b = new Derived();
    b->f();

    // downcasting we can use static_cast or down_cast
    Derived* d = static_cast<Derived*>(b);

    d->f();
    d->g();

    delete b;
}

template <typename Derived, typename Base>
Derived dynamic_unique_pointer_cast(std::unique_ptr<Base>& basePtr)
{
    Derived derivedPtr = dynamic_cast<Derived>(basePtr.get());
    return derivedPtr;
}

template <typename Derived, typename Base>
std::unique_ptr<Derived> dynamic_unique_ptr_cast(std::unique_ptr<Base>&& ptr)
{
    if (auto* derivedPtr = dynamic_cast<Derived*>(ptr.get()))
    {
        ptr.release();
        return std::unique_ptr<Derived>(derivedPtr);
    }
    return nullptr;
}

void shared_pointer_casting()
{
    std::cout << "========== Shared Pointer casting =========== \n";
    std::shared_ptr<Base> basePtr = std::make_shared<Derived>();

    // Downcasting with static_cast
    // std::static_pointer_cast<Derived>(basePtr)->g(); // (constructs a temporary shared_ptr, then calls operator->)
    // static_cast<Derived*>(basePtr.get())->g(); //(direct cast, does not construct a temporary shared_ptr)

    // Downcasting safely at runtime
    // Use dynamic_pointer_cast to check the actual type
    std::shared_ptr<Derived> derivedFromBasePtr = std::dynamic_pointer_cast<Derived>(basePtr);

    if (derivedFromBasePtr)
    {
        std::cout << "Cast to Derived succeeded: ";
        derivedFromBasePtr->g();  // Can access Derived functions
    }
    else
    {
        std::cout << "Cast to Derived failed." << std::endl;
    }

    std::shared_ptr<Base> baseOnlyPtr = std::make_shared<Base>();
    std::shared_ptr<Derived> failedCast = std::dynamic_pointer_cast<Derived>(baseOnlyPtr);

    if (!failedCast)
    {
        std::cout << "Cast failed as expected (object is really a Base)." << std::endl;
    }
}

void unique_pointer_casting()
{
    std::unique_ptr<Base> base_ptr = std::make_unique<Derived>();

    // Correct and safe down casting
    // Get a raw pointer and cast it
    Derived* raw_derived_ptr = dynamic_cast<Derived*>(base_ptr.get());

    if (raw_derived_ptr)
    {
        raw_derived_ptr->g();
    }

    Derived* new_raw_derived_ptr = dynamic_unique_pointer_cast<Derived*>(base_ptr);

    if (new_raw_derived_ptr)
    {
        new_raw_derived_ptr->g();
    }

    // Using C++23 std::dynamic_pointer_cast not working
    // std::unique_ptr<Derived> derived_ptr = std::dynamic_pointer_cast<Derived>(std::move(base_ptr));

    // if (derived_ptr) {
    //     derived_ptr->g();
    // } else {
    //     std::cout << "Cast failed\n";
    // }
}

int main()
{
    unique_pointer_casting();
}