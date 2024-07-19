/**
 * @file recursive_mutex.cpp
 * @author Saikiran Nadipilli
 * @brief 
 * @version 0.1
 * @date 2024-07-11
 * 
 * @copyright Copyright (c) 2024
 * 
 */

/**
 * https://en.cppreference.com/w/cpp/thread/recursive_mutex
 * @brief Recursive Mutex is a synchronization primitive that can be used to protect shared data
 * from being simultaneously accessed by multiple threads.
 * 
 * recursive mutex offers exclusive and recursive ownership.
 * 
 * A calling threads owns a recursive_mutex that successfully acquire lock or try_lock, during that period 
 * the thread may additional calls to lock or try_lock. Ownership will ends when the thread makes additional 
 * calls to unlock.
 * 
 * When a thread owns a recursive_mutex, all other threads will block. 
 * 
 */

#include <iostream>
#include <thread>
#include <mutex>

int value = 0;
std::recursive_mutex rc;

void func1()
{
    std::lock_guard lc(rc);
    value = 20;
    std::cout << "value in func1: " << value << "\n";
}

void func()
{
    std::lock_guard lc(rc);
    value = 10;
    std::cout << "value in func: " << value << "\n";
    func1();
    std::cout << "value again in func: " << value << "\n";
}

int main()
{
    std::thread t1(func);
    std::thread t2(func1);

    t1.join();
    t2.join();
}