/**
 * @file memory_order_relax.cpp
 * @author Saikiran Nadipilli (saikirannadipilli@gmail.com)
 * @brief
 * @version 0.1
 * @date 2026-03-10
 *
 * @copyright Copyright (c) 2026
 *
 */

#include <assert.h>
#include <atomic>
#include <iostream>
#include <thread>

// Relaxed operation: there are no synchronization or ordering constraints imposed on other reads or writes,
//  only this operation's atomicity is guaranteed (see Relaxed ordering below).

std::atomic_bool x = false;
std::atomic_bool y = false;
std::atomic_int z = 0;

void write_x_then_y()
{
    x.store(true, std::memory_order_relaxed);
    y.store(true, std::memory_order_relaxed);
}

void read_y_then_x()
{
    while (!y.load(std::memory_order_relaxed))
        ;

    if (x.load(std::memory_order_relaxed))
    {
        ++z;
    }
}

void run_code()
{
    std::thread t1(write_x_then_y);
    std::thread t2(read_y_then_x);

    t1.join();
    t2.join();

    assert(z != 0);
}

int main()
{
    run_code();
    return 0;
}