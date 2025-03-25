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

int main()
{
    Foo<int> fooObj;

    fooObj.bar<float>();

    func(fooObj);
    func(&fooObj);
    func<int>();

    Foobar<int> fooBarObj;

    fooBarObj.template bar<float>();

    return 0;
}