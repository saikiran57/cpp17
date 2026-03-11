/**
 * @file weak_ptr.cpp
 * @author Saikiran Nadipilli (saikirannadipilli@gmail.com)
 * @brief
 * @version 0.1
 * @date 2026-02-12
 *
 * @copyright Copyright (c) 2026
 *
 */

#include <iostream>
#include <memory>

struct Foo
{
    Foo()
    {
        std::cout << "Foo constructed\n";
    }
    ~Foo()
    {
        std::cout << "Foo destructed\n";
    }
};

int main()
{
    std::weak_ptr<Foo> wp;

    {
        std::shared_ptr<Foo> sp = std::make_shared<Foo>();
        wp = sp;

        std::cout << "Inside block use_count: " << wp.use_count() << "\n";

        {
            // lock() creates a temporary shared_ptr
            auto tmp = wp.lock();
            std::cout << "Inside inner block use_count (with tmp): " << wp.use_count() << "\n";
        }

        std::cout << "After tmp destroyed use_count: " << wp.use_count() << "\n";
    }

    std::cout << "Outside block, weak expired? " << (wp.expired() ? "YES" : "NO") << "\n";
}