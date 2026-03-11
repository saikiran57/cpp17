/**
 * @file sequenctial_consistency.cpp
 * @author Saikiran Nadipilli (saikirannadipilli@gmail.com)
 * @brief
 * @version 0.1
 * @date 2026-03-10
 *
 * @copyright Copyright (c) 2026
 *
 */

#include <atomic>
#include <cassert>
#include <thread>

std::atomic<bool> x = {false};
std::atomic<bool> y = {false};
std::atomic<int> z = {0};

void write_x()
{
    x.store(true, std::memory_order_relaxed);  // a store performs a release operation
}

void write_y()
{
    y.store(true, std::memory_order_relaxed);  // a store performs a release operation
}

void read_x_then_y()
{
    while (!x.load(std::memory_order_relaxed))  // A load operation with this memory order performs an acquire operation
        ;
    if (y.load(std::memory_order_relaxed))
        ++z;  // A load operation with this memory order performs an acquire operation
}

void read_y_then_x()
{
    while (!y.load(std::memory_order_relaxed))
        ;
    if (x.load(std::memory_order_relaxed)) ++z;
}

int main()
{
    std::thread a(write_x);
    std::thread b(write_y);
    //    std::thread c(read_x_then_y);
    std::thread d(read_y_then_x);
    a.join();
    b.join();
    // c.join();
    d.join();
    assert(z.load() != 0);  // will never happen
}