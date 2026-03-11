// #include <iostream>

// // ----- Custom vtable definition -----
// struct VTable
// {
//     void (*foo)(void*);
//     void (*bar)(void*);
// };

// // ----- "Base" -----
// struct Base
// {
//     VTable* vtable;
// };

// void base_foo(void* self)
// {
//     std::cout << "Base::foo (manual)\n";
// }
// void base_bar(void* /*self*/)
// {
//     std::cout << "Base::bar (manual)\n";
// }

// // "global" vtable for Base
// VTable base_vtable = {&base_foo, &base_bar};

// // ----- "Derived" -----
// struct Derived
// {
//     VTable* vtable;  // must be first field (same layout)
// };

// void derived_foo(void* self)
// {
//     std::cout << "Derived::foo (manual)\n";
// }
// void derived_bar(void* /*self*/)
// {
//     std::cout << "Derived::bar (manual)\n";
// }

// // another global vtable for Derived
// VTable derived_vtable = {&derived_foo, &derived_bar};

// // ---- "dispatch" utilities ----
// void call_foo(Base* obj)
// {
//     obj->vtable->foo(obj);
// }

// void call_bar(Base* obj)
// {
//     obj->vtable->bar(obj);
// }

// int main()
// {
//     // Create a Base object
//     Base b;
//     b.vtable = &base_vtable;

//     // Create a Derived object
//     Derived d;
//     d.vtable = &derived_vtable;

//     // Polymorphic calls
//     call_foo(&b);  // Base::foo
//     call_bar(&b);  // Base::bar

//     call_foo(reinterpret_cast<Base*>(&d));  // Derived::foo
//     call_bar(reinterpret_cast<Base*>(&d));  // Derived::bar
// }

// #include <iostream>

// // We forward declare Base because function pointer needs it.
// struct Base;

// // Function pointer type that matches "member functions"
// using FuncPtr = void(*)(Base*);

// // ------------------------------------------------------------
// // 1. Custom Virtual Table
// // ------------------------------------------------------------
// struct VTable {
//     FuncPtr function1;
//     FuncPtr function2;
// };

// // ------------------------------------------------------------
// // 2. Base class (NO real virtual keyword)
// // ------------------------------------------------------------
// struct Base {
//     VTable* vptr;   // manual virtual pointer

//     Base(VTable* vt) : vptr(vt) {}

//     // Manual "virtual calls"
//     void function1() { vptr->function1(this); }
//     void function2() { vptr->function2(this); }
// };

// // ------------------------------------------------------------
// // 3. Derived class
// // ------------------------------------------------------------
// struct Derived : Base {
//     Derived(VTable* vt) : Base(vt) {}
// };

// // ------------------------------------------------------------
// // 4. Implementations of functions for Base
// // ------------------------------------------------------------
// void Base_function1(Base*) {
//     std::cout << "Base::function1\n";
// }
// void Base_function2(Base*) {
//     std::cout << "Base::function2\n";
// }

// // ------------------------------------------------------------
// // 5. Implementations of functions for Derived
// // ------------------------------------------------------------
// void Derived_function1(Base*) {
//     std::cout << "Derived::function1\n";
// }
// void Derived_function2(Base*) {
//     std::cout << "Derived::function2\n";
// }

// // ------------------------------------------------------------
// // 6. Create actual virtual tables (just like compiler does)
// // ------------------------------------------------------------
// VTable Base_vtable = {
//     &Base_function1,
//     &Base_function2
// };

// VTable Derived_vtable = {
//     &Derived_function1,
//     &Derived_function2
// };

// // ------------------------------------------------------------
// // 7. Demonstration of manual dynamic dispatch
// // ------------------------------------------------------------
// int main() {
//     Base b(&Base_vtable);
//     Derived d(&Derived_vtable);

//     Base* ptr1 = &b;
//     Base* ptr2 = &d;   // Base pointer → Derived object

//     std::cout << "Calling through Base object:\n";
//     ptr1->function1();
//     ptr1->function2();

//     std::cout << "\nCalling through Derived object (via Base*):\n";
//     ptr2->function1();   // Calls Derived::function1
//     ptr2->function2();   // Calls Derived::function2

//     return 0;
// }

// #include <iostream>
// #include <array>

// class A {
// public:
//     A() : x(0) {
//         std::cout << "A ctor\n";

//         data = {
//             &A::add,
//             &A::sub,
//             &A::mul
//         };
//     }

//     void add() { x += 2; }
//     void sub() { std::cout << "x called: " << x << "\n"; x -= 2; }
//     void mul() { x *= 2; }

//     int x;

//     // PURE member function pointers
//     std::array<void (A::*)(), 3> data;
// };

// class B : public A {
// public:
//     B(int v) : y(v) {
//         // Override only the first entry in A's table
//         data[0] = static_cast<void (A::*)()>(&B::add);
//     }

//     void add() { std::cout << "x called" << x << "\n"; x += 4; }  // This is NOT virtual, just a new function in B

//     int y;
// };

// int main() {
//     A aobj;
//     B obj(2);

//     A* obj2 = &obj;

//     // Calling A::sub (because data[1] = &A::sub)
//     (obj2->*obj2->data[1])();

//     // Calling B::add (because obj modified data[0])
//     (obj2->*obj2->data[0])();

//     std::cout << "obj2->x = " << obj2->x << "\n";

//     // Call A::sub on aobj
//     (aobj.*aobj.data[1])();

//     std::cout << "aobj.x = " << aobj.x << "\n";

//     return 0;
// }

// #include <iostream>

// class A {
// public:
//     using fn = void (*)(A*);

//     struct vtable {
//         fn add;
//         fn sub;
//         fn mul;
//     };

//     static constexpr vtable a_vt = {
//         [](A* a){ a->add(); },
//         [](A* a){ a->sub(); },
//         [](A* a){ a->mul(); }
//     };

//     A() : vt(&a_vt), x(0) {}

//     // Normal methods
//     void add() { x += 2; }
//     void sub() { std::cout << "A::sub x=" << x << "\n"; x -= 2; }
//     void mul() { x *= 2; }

//     void call_add() { vt->add(this); }
//     void call_sub() { vt->sub(this); }
//     void call_mul() { vt->mul(this); }

//     const vtable* vt;
//     int x;
// };

// class B : public A {
// public:
//     static constexpr vtable b_vt = {
//         [](A* a){ static_cast<B*>(a)->add(); }, // override add
//         a_vt.sub,                               // inherit sub
//         a_vt.mul                                // inherit mul
//     };

//     B(int v) : y(v) {
//         vt = &b_vt;  // override table
//     }

//     void add() { std::cout << "B::add x=" << x << "\n"; x += 4; }

//     int y;
// };

// int main() {
//     A a;
//     B b(2);

//     A* p = &b;

//     p->call_sub();  // A::sub
//     p->call_add();  // B::add
//     p->call_mul();  // A::mul

//     std::cout << "b.x = " << b.x << "\n";

//     return 0;
// }

#include <iostream>

class A
{
public:
    using fn = void (*)(A*);

    struct vtable
    {
        fn add;
        fn sub;
        fn mul;
    };

    static const vtable a_vt;  // declaration only

    A() : x(0), vptr(&a_vt)
    {
        std::cout << "A ctor\n";
    }

    void add()
    {
        x += 2;
    }
    void sub()
    {
        std::cout << "A::sub x=" << x << "\n";
        x -= 2;
    }
    void mul()
    {
        x *= 2;
    }

    void call_add()
    {
        vptr->add(this);
    }
    void call_sub()
    {
        vptr->sub(this);
    }
    void call_mul()
    {
        vptr->mul(this);
    }

    int x;
    const vtable* vptr;
};

class B : public A
{
public:
    static const vtable b_vt;

    B(int v) : y(v)
    {
        vptr = &b_vt;
    }

    void add()
    {
        std::cout << "B::add, old x=" << x << "\n";
        x += 4;
    }

    int y;
};

// ---------------------------
// DEFINE VTABLES **AFTER** CLASSES
// ---------------------------

// A's vtable
const A::vtable A::a_vt = {[](A* a) {
                               a->add();
                           },
                           [](A* a) {
                               a->sub();
                           },
                           [](A* a) {
                               a->mul();
                           }};

// B's vtable
const A::vtable B::b_vt = {
    [](A* a) {
        static_cast<B*>(a)->add();
    },            // override add
    A::a_vt.sub,  // inherit sub
    A::a_vt.mul   // inherit mul
};

int main()
{
    A a;
    B b(2);

    A* p = &b;

    p->call_sub();  // A::sub
    p->call_add();  // B::add
    p->call_mul();  // A::mul

    std::cout << "p->x = " << p->x << "\n";
    return 0;
}