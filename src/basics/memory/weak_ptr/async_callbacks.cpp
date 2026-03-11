/**
 * @file async_callbacks.cpp
 * @author Saikiran Nadipilli (saikirannadipilli@gmail.com)
 * @brief
 * @version 0.1
 * @date 2026-02-24
 *
 * @copyright Copyright (c) 2026
 *
 */

#include <future>
#include <iostream>
#include <memory>
#include <thread>

struct Test
{
    Test(int val) : a(val)
    {
        std::cout << "constructed \n";
    }
    ~Test()
    {
        std::cout << "destructed \n";
    }
    int a;
};

int main()
{
    std::shared_ptr<Test> test = std::make_shared<Test>(10);
    std::weak_ptr<Test> wtest = test;

    auto fet = std::async(std::launch::async, [wtest]() {
        std::cout << "Inside a thread\n";

        // Check immediately
        if (auto t = wtest.lock())
        {
            std::cout << "Object alive initially\n";
        }

        std::this_thread::sleep_for(std::chrono::seconds(3));

        // Check after delay
        if (auto t = wtest.lock())
        {
            std::cout << "Object still alive: " << t->a << "\n";
        }
        else
        {
            std::cout << "Object was destroyed during sleep\n";
        }
    });

    std::this_thread::sleep_for(std::chrono::seconds(1));
    test.reset();  // Object destroyed while async is sleeping
    fet.get();
    return 0;
}