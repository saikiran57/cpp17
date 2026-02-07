/**
 * @file two_phase_name_lookup.cpp
 * @author Saikiran Nadipilli (saikirannadipilli@gmail.com)
 * @brief TWO-PHASE NAME LOOKUP - Complete Reference
 * @version 1.0
 * @date 2026-02-06
 *
 * https://eli.thegreenplace.net/2012/02/06/dependent-name-lookup-for-c-templates
 *
 * @copyright Copyright (c) 2026
 *
 * TWO-PHASE NAME LOOKUP OVERVIEW:
 * ==============================
 * Templates are processed in two phases:
 * - Phase 1 (Definition time): Non-dependent names are resolved
 * - Phase 2 (Instantiation time): Dependent names are resolved using ADL
 *
 * TERMINOLOGY:
 * - Dependent Name: name that depends on template parameter(s)
 * - Non-dependent Name: name that doesn't depend on template parameters
 * - ADL (Argument Dependent Lookup): looks up names in namespaces of arguments
 */

#include <iostream>
#include <type_traits>
#include <vector>

namespace
{

// ============================================================================
// CASE 1: NON-DEPENDENT NAMES (Phase 1 - Definition Time Lookup)
// ============================================================================

std::string global_str = "Global function";

void helper()
{
    std::cout << "::helper() called\n";
}

template <typename T>
class Template1
{
public:
    void test()
    {
        // Non-dependent: 'helper' doesn't depend on T
        // Resolved at definition time using unqualified lookup
        // If helper() doesn't exist NOW, ERROR at definition time
        helper();  // ✓ OK: found in global scope
    }
};

// ============================================================================
// CASE 2: DEPENDENT NAMES (Phase 2 - Instantiation Time Lookup)
// ============================================================================

template <typename T>
class Base
{
public:
    void baseHelper()
    {
        std::cout << "Base::baseHelper()\n";
    }
};

template <typename T>
class Template2 : public Base<T>
{  // Dependent base class
public:
    void test()
    {
        // ERROR: baseHelper() is dependent (comes from Base<T>)
        // Compiler doesn't look in Base<T> during Phase 1
        // baseHelper();  // ❌ ERROR: unqualified lookup doesn't find it

        // ✓ SOLUTIONS:
        // 1. Use this->
        this->baseHelper();

        // 2. Use explicit scope
        Base<T>::baseHelper();

        // 3. Use using declaration
    }
};

// ============================================================================
// CASE 3: DEPENDENT FUNCTION CALLS - ADL (Argument Dependent Lookup)
// ============================================================================

namespace MyNamespace
{
struct MyType
{
    int value = 42;
};

// ADL will find this in MyNamespace when called with MyType argument
void process(const MyType& obj)
{
    std::cout << "MyNamespace::process() - value: " << obj.value << "\n";
}
}

template <typename T>
void adlTemplate(T obj)
{
    // If T = MyType, this call uses ADL to find process() in MyNamespace
    // This is dependent lookup at instantiation time
    process(obj);  // ✓ OK: ADL finds process in MyNamespace when T=MyType
}

// ============================================================================
// CASE 4: EXPLICITLY SCOPED NAMES (Always Phase 1 Lookup)
// ============================================================================

template <typename T>
class Template3
{
public:
    void test()
    {
        // Using ::helper() forces non-dependent lookup
        ::helper();  // ✓ OK: always looks in global scope at definition time

        // Using std::cout is fully qualified (non-dependent)
        std::cout << "Non-dependent\n";  // ✓ OK
    }
};

// ============================================================================
// CASE 5: USING DECLARATIONS (Enable dependent lookup)
// ============================================================================

template <typename T>
class Template4 : public Base<T>
{
    // Using declaration makes baseHelper "available" for unqualified lookup
    using Base<T>::baseHelper;

public:
    void test()
    {
        // Now this works because of using declaration
        baseHelper();  // ✓ OK: found via using declaration
    }
};

// ============================================================================
// CASE 6: DEPENDENT TEMPLATE NAMES - typename/template keywords
// ============================================================================

template <typename T>
struct Container
{
    using value_type = typename T::value_type;
    template <typename U>
    using rebind = typename T::template rebind<U>;
};

template <typename T>
class Template5
{
public:
    void test()
    {
        // Must use 'typename' keyword for dependent type names
        typename T::value_type val;  // ✓ OK: typename tells compiler this is a type

        // Must use 'template' keyword for dependent template names
        typename T::template rebind<int> rebound;  // ✓ OK: template keyword
    }
};

// ============================================================================
// CASE 7: STATIC MEMBERS (Non-dependent if class is non-dependent)
// ============================================================================

struct GlobalClass
{
    static int staticValue;
};

int GlobalClass::staticValue = 100;

template <typename T>
void Template6()
{
    // GlobalClass is non-dependent, so this is Phase 1 lookup
    std::cout << GlobalClass::staticValue << "\n";  // ✓ OK: Phase 1
}

// ============================================================================
// CASE 8: DEPENDENT STATIC MEMBERS
// ============================================================================

template <typename T>
void Template7()
{
    // T is a template parameter, so T::staticValue is dependent
    // Resolved at instantiation time using unqualified lookup in T's scope
    int x = T::staticValue;  // Dependent lookup at Phase 2
}

// ============================================================================
// CASE 9: FRIEND FUNCTIONS (ADL Case)
// ============================================================================

namespace FriendDemo
{
template <typename T>
class MyClass
{
    T data;

public:
    MyClass(T d) : data(d) {}

    // Friend function declaration inside template
    // Will be found via ADL when instantiated
    friend void friendFunc(const MyClass& obj)
    {
        std::cout << "Friend function called\n";
    }
};
}

template <typename T>
void callFriend(const FriendDemo::MyClass<T>& obj)
{
    // This works via ADL - compiler finds friendFunc using MyClass's namespace
    friendFunc(obj);  // ✓ OK: ADL finds friend function
}

// ============================================================================
// CASE 10: HIDDEN FRIEND IDIOM (ADL Magic)
// ============================================================================

class Vector
{
    double x, y;

public:
    Vector(double x = 0, double y = 0) : x(x), y(y) {}

    friend std::string operator+(const Vector& a, const Vector& b)
    {
        return "Vector addition via friend";
    }
};

template <typename T>
std::string add(const T& a, const T& b)
{
    // This finds operator+ via ADL when T = Vector
    return a + b;  // ✓ OK: ADL finds friend operator+
}

// ============================================================================
// CASE 11: DEPENDENT NAME WITH MULTIPLE OVERLOADS
// ============================================================================

namespace OverloadDemo
{
void process(int x)
{
    std::cout << "process(int)\n";
}
void process(double x)
{
    std::cout << "process(double)\n";
}

template <typename T>
struct Wrapper
{
    T value;
};

void process(const Wrapper<int>& w)
{
    std::cout << "process(Wrapper<int>)\n";
}
}

template <typename T>
void callProcess(T value)
{
    // ADL looks in OverloadDemo namespace when T is from there
    OverloadDemo::process(value);  // ✓ Explicit qualification
}

// ============================================================================
// CASE 12: INHERITED TEMPLATE MEMBERS
// ============================================================================

template <typename T>
struct BaseTemplate
{
    template <typename U>
    void method()
    {
        std::cout << "BaseTemplate::method<" << typeid(U).name() << ">\n";
    }
};

template <typename T>
struct DerivedTemplate : BaseTemplate<T>
{
    void callBaseMethod()
    {
        // WRONG: method is dependent on T
        // this->template method<int>();  ✓ Correct: needs 'template' keyword
        // OR
        BaseTemplate<T>::template method<int>();  // ✓ Correct
    }
};

// ============================================================================
// CASE 13: NAME SHADOWING IN TEMPLATES
// ============================================================================

namespace ShadowDemo
{
void func()
{
    std::cout << "Global func\n";
}

template <typename T>
class Template
{
    // Defining local func doesn't affect template body
    void func()
    {
        std::cout << "Local func\n";
    }

public:
    void test()
    {
        // Phase 1: looks for unqualified 'func' -> finds in global scope
        func();  // Calls global func, NOT local member func
    }
};
}

// ============================================================================
// CASE 14: DEPENDENT vs NON-DEPENDENT DISTINCTION
// ============================================================================

template <typename T>
class ComplexTemplate
{
public:
    void complexTest()
    {
        // Non-dependent (can check now)
        std::cout << "This compiles\n";  // Phase 1

        // Dependent (checked at instantiation)
        T obj;  // Phase 2 (when T is known)

        // Dependent on T (Phase 2)
        typename T::nested_type x;  // Phase 2

        // Non-dependent (Phase 1)
        int y = 5;  // Phase 1
    }
};

// ============================================================================
// CASE 15: EXPLICIT TEMPLATE ARGUMENTS (Suppress ADL Sometimes)
// ============================================================================

namespace ExplicitDemo
{
struct Type
{
};
void mystery(const Type& t)
{
    std::cout << "ExplicitDemo::mystery\n";
}
}

template <typename T>
void caller(T t)
{
    // With explicit scope, uses Phase 1 lookup (no ADL)
    ::ExplicitDemo::mystery(t);  // ✓ Phase 1: explicit qualification

    // Without explicit scope, uses Phase 2 ADL
    // mystery(t);  // Would use ADL if enabled
}

// ============================================================================
// COMPLETE SUMMARY TABLE
// ============================================================================
/*
┌─────────────────────────────────────────────────────────────────────────┐
│ PHASE 1 vs PHASE 2 LOOKUP SUMMARY                                      │
├─────────────────────────────────────────────────────────────────────────┤
│ NON-DEPENDENT NAMES (Phase 1 - Definition Time)                        │
├─────────────────────────────────────────────────────────────────────────┤
│ • Global functions: func()                                              │
│ • Global variables: global_var                                          │
│ • Standard library: std::cout, std::vector                              │
│ • Explicitly qualified: ::func(), Namespace::func()                     │
│ • Non-dependent class members                                           │
│ • Primitive types: int, double                                          │
│ Resolution: Unqualified lookup at definition time                       │
│                                                                         │
├─────────────────────────────────────────────────────────────────────────┤
│ DEPENDENT NAMES (Phase 2 - Instantiation Time)                         │
├─────────────────────────────────────────────────────────────────────────┤
│ • Function parameters: void func(T)                                     │
│ • Class members: Base<T>::member                                        │
│ • Member functions: this->member(), Base<T>::func()                     │
│ • Nested types: T::type, typename T::type                               │
│ • ADL calls: func(template_param)                                       │
│ Resolution: ADL + unqualified lookup at instantiation time              │
│                                                                         │
├─────────────────────────────────────────────────────────────────────────┤
│ SOLUTIONS TO PHASE 1 ERRORS                                            │
├─────────────────────────────────────────────────────────────────────────┤
│ 1. this->member()           - Defer to Phase 2                         │
│ 2. Base<T>::member()        - Explicit scope                            │
│ 3. using Base<T>::member;   - Bring into scope                          │
│ 4. template keyword         - For member templates                       │
│ 5. typename keyword         - For dependent types                       │
└─────────────────────────────────────────────────────────────────────────┘
*/

// ============================================================================
// PRACTICAL EXAMPLES - COMMON MISTAKES AND FIXES
// ============================================================================

// MISTAKE 1: Assuming member lookup in dependent base classes
template <typename T>
class BadTemplate : public Base<T>
{
    // void badTest() {
    //     baseHelper();  // ❌ ERROR: depends on Base<T>
    // }
};

// FIX 1: Use this->
template <typename T>
class GoodTemplate1 : public Base<T>
{
    void goodTest()
    {
        this->baseHelper();  // ✓ OK: Phase 2 dependent lookup
    }
};

// FIX 2: Use explicit qualification
template <typename T>
class GoodTemplate2 : public Base<T>
{
    void goodTest()
    {
        Base<T>::baseHelper();  // ✓ OK: explicit scope
    }
};

// MISTAKE 2: Forgetting typename for dependent types
template <typename T>
class TypeMistake
{
    // using value_t = T::value_type;  // ❌ ERROR: might be non-type member
};

// FIX: Use typename keyword
template <typename T>
class TypeFix
{
    using value_t = typename T::value_type;  // ✓ OK: tells compiler this is a type
};

// MISTAKE 3: Forgetting template keyword for member templates
template <typename T>
class TemplateMistake
{
    // void bad() {
    //     T::template_member<int> x;  // ❌ ERROR: ambiguous without 'template'
    // }
};

// FIX: Use template keyword
template <typename T>
class TemplateFix
{
    void good()
    {
        typename T::template nested<int> x;  // ✓ OK: 'template' keyword clarifies
    }
};