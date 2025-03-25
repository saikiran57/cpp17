/**
 * @file shared_mutex.cpp
 * @author Saikiran Nadipilli
 * @brief
 * @version 0.1
 * @date 2024-07-11
 *
 * @copyright Copyright (c) 2024
 *
 */

/**
 * https://en.cppreference.com/w/cpp/thread/shared_mutex
 * @brief Shared mutex is a synchronization primitive that can be used to protect shared data
 * from begin simultaneously accessed by multiple threads.
 *
 * shared_mutex has exclusive and shared ownership.
 *
 * If one thread has acquired the exclusive lock, no other thread can acquire the lock(including shared lock)
 *
 * If one thread has acquired the shared lock, no other thread can acquire the lock exclusive lock, but can
 * acquire the shared lock.
 *
 * Within one thread only one lock(exclusive or shared) can be acquired by the same time.
 *
 * Shared mutexes are especially useful when shared data can be safely read my multiple threads simultaneously.
 * but a thread may only write the same data when no other thread is reading or writing.
 */

#include <cstddef>
#include <iostream>
#include <mutex>
#include <shared_mutex>
#include <thread>

static int value = 0;
static std::shared_mutex sm;

// multiple threads can read the value at the same time
static int get()
{
    std::shared_lock const sl(sm);
    return value;
}

// only one thread can write the value
static void increment()
{
    std::unique_lock const lk(sm);
    ++value;
}

int main()
{
    auto func = []() {
        for (size_t i = 0; i < 5; i++)
        {
            increment();
            std::cout << "get value : " << std::this_thread::get_id() << ":" << get() << "\n";
        }
    };

    std::thread t1(func);
    std::thread t2(func);

    t1.join();
    t2.join();
}
