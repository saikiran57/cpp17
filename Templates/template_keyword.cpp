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
struct foo
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
struct foo_base
{
    template <typename U>
    void base_bar()
    {
        std::cout << "Base bar()\n";
    }
};

template <typename T>
struct foobar : public foo_base<T>
{
    template <typename U>
    void bar()
    {
        this->template base_bar<U>();
    }
};

template <typename T>
void func(foo<T> f)
{
    std::cout << "func()\n";
    f.template bar<float>();
    f.newBar();
}

template <typename T>
void func(foo<T>* fp)
{
    fp->template bar<float>();
}

template <typename T>
void func()
{
    foo<T>::template sbar<float>();
}

int main()
{
    foo<int> fooObj;

    fooObj.bar<float>();

    func(fooObj);
    func(&fooObj);
    func<int>();

    foobar<int> fooBarObj;

    fooBarObj.template bar<float>();

    return 0;
}