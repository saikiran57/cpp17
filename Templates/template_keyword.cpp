/**
 * @file template_keyword.cpp
 * @author Saikiran Nadipilli
 * @brief
 * @version 0.1
 * @date 2024-12-27
 *
 * @copyright Copyright (c) 2024
 *
 * https://www.aerialmantis.co.uk/blog/2017/03/17/template-keywords/
 *
 */

#include <iostream>

template <typename T>
struct Foo
{
    template <typename U>
    void bar()
    {
        std::cout << "bar()\n";
    }

    template <typename U>
    static void sbar()
    {
        std::cout << "static bar()\n";
    }

    void newBar()
    {
        std::cout << "newBar()\n";
    }
};

template <typename T>
struct FooBase
{
    template <typename U>
    void baseBar()
    {
        std::cout << "Base bar()\n";
    }
};

template <typename T>
struct Foobar : public FooBase<T>
{
    template <typename U>
    void bar()
    {
        this->template baseBar<U>();
    }
};

template <typename T>
static void func(Foo<T> f)
{
    std::cout << "func()\n";
    f.template bar<float>();
    f.newBar();
}

template <typename T>
static void func(Foo<T>* fp)
{
    fp->template bar<float>();
}

template <typename T>
static void func()
{
    Foo<T>::template sbar<float>();
}

// Typename Keyword

template <typename T>
struct type_or_value;

template <>
struct type_or_value<int>
{
    static constexpr bool tv = true;
};

template <>
struct type_or_value<float>
{
    using tv = float;
};

template <typename T>
struct foo
{
};

template <typename T>
void funcType()
{
    bool v = type_or_value<T>::tv;

    /**
     * When the compiler parses code like this involving a dependent type,
     * in this case, type_or_value<T> it cannot know whether the member tv resolves to a type or a non-type and assumes
     * the latter. In order to instruct the compiler that tv is, in fact, resolves to a type it is necessary to add the
     * typename keyword immediately before the expression:
     *
     */
    foo<typename type_or_value<T>::tv> f;
}

int main()
{
    Foo<int> fooObj;

    fooObj.bar<float>();

    func(fooObj);
    func(&fooObj);
    func<int>();

    Foobar<int> fooBarObj;

    fooBarObj.template bar<float>();

    funcType<float>();

    return 0;
}