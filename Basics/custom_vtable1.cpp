#include <iostream>

// ----- Custom vtable definition -----
struct VTable
{
    void (*foo)(void*);
    void (*bar)(void*);
};

// ----- "Base" -----
struct Base
{
    VTable* vtable;
};

void base_foo(void* self)
{
    std::cout << "Base::foo (manual)\n";
}
void base_bar(void* /*self*/)
{
    std::cout << "Base::bar (manual)\n";
}

// "global" vtable for Base
VTable base_vtable = {&base_foo, &base_bar};

// ----- "Derived" -----
struct Derived
{
    VTable* vtable;  // must be first field (same layout)
};

void derived_foo(void* self)
{
    std::cout << "Derived::foo (manual)\n";
}
void derived_bar(void* /*self*/)
{
    std::cout << "Derived::bar (manual)\n";
}

// another global vtable for Derived
VTable derived_vtable = {&derived_foo, &derived_bar};

// ---- "dispatch" utilities ----
void call_foo(Base* obj)
{
    obj->vtable->foo(obj);
}

void call_bar(Base* obj)
{
    obj->vtable->bar(obj);
}

int main()
{
    // Create a Base object
    Base b;
    b.vtable = &base_vtable;

    // Create a Derived object
    Derived d;
    d.vtable = &derived_vtable;

    // Polymorphic calls
    call_foo(&b);  // Base::foo
    call_bar(&b);  // Base::bar

    call_foo(reinterpret_cast<Base*>(&d));  // Derived::foo
    call_bar(reinterpret_cast<Base*>(&d));  // Derived::bar
}
