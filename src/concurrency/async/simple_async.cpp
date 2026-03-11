/**
 * @file simple_async.cpp
 * @author Saikiran Nadipilli (saikirannadipilli@gmail.com)
 * @brief
 * @version 0.1
 * @date 2026-03-02
 *
 * @copyright Copyright (c) 2026
 *
 */

#include <future>
#include <iostream>
#include <mutex>
#include <thread>

std::mutex mu;

void print(const std::string& data)
{
    std::cout << "Worker Thread Id:" << std::this_thread::get_id() << " Data: " << data << "\n";
}

struct Stats
{
    int health;
    Stats()
    {
        std::cout << "Stats Const\n";
    }
    Stats(int value) : health(value)
    {
        std::cout << "Stats param Constructor\n";
    }
    ~Stats()
    {
        std::cout << "Stats Destructor\n";
    }
};

class Test
{
public:
    Test()
    {
        std::cout << "Test constructor \n";
    }
    ~Test()
    {
        std::cout << "Test destructor \n";
    }
    Test(const Test& obj)
    {
        std::cout << "Test copy constructor \n";
    }
    Test(Test&& obj)
    {
        std::cout << "Test move constructor \n";
    }
    void print(const std::string& data, int value)
    {
        std::scoped_lock lk(mu);
        std::cout << "data: " << data << " Value: " << value << "\n";
    }

    int bar(int value)
    {
        std::lock_guard<std::mutex> lk(mu);
        return value + 10;
    }

    void foo(const Stats& stats)
    {
        std::cout << "Stats: " << stats.health << "\n";
    }
};

int main()
{
    // std::string data = "Hello world";
    // std::future ft = std::async(std::launch::async, print, data);

    // std::cout << "Main Thread Id:" << std::this_thread::get_id() <<" Data: " << data << "\n";
    // ft.get();
    // // ft.get(); if we call again it will crash so instead of using std::future use std::shared_future

    // Test tObj;
    // int value = 10;
    // std::future ft2 = std::async(&Test::print, &tObj, data, value);
    // ft2.get();

    // auto ft3 = std::async(std::launch::async, &Test::bar, &tObj, value);

    // std::cout << "ft3 value: " << ft3.get() << "\n";

    Test tObj;
    Stats stats(100);
    // tObj.foo(stats);
    auto ft4 = std::async(&Test::foo, &tObj, std::ref(stats));

    // ft4.get();

    return 0;
}