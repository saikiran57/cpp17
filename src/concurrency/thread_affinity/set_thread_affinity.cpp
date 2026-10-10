/**
 * @file set_thread_affinity.cpp
 * @author Saikiran Nadipilli (saikirannadipilli@gmail.com)
 * @brief
 * @version 0.1
 * @date 2026-03-16
 *
 * @copyright Copyright (c) 2026
 *
 */

#include <iostream>
#include <pthread.h>
#include <sched.h>
#include <thread>

/**
 * CPU core pinning, also known as CPU 𝐚𝐟𝐟𝐢𝐧𝐢𝐭𝐲, is the process of binding a specific thread or process to a particular
 * CPU core. This can optimize performance by reducing context switching and cache invalidation. Here's a complete guide
 * on how to pin a thread to a specific CPU core in C+
 */

void pin_thread(int cpu)
{
    cpu_set_t cpuset;
    CPU_ZERO(&cpuset);
    CPU_SET(cpu, &cpuset);

    auto result = pthread_setaffinity_np(pthread_self(), sizeof(cpu_set_t), &cpuset);

    if (result != 0)
    {
        std::cerr << "Error setting thread affinity: " << result << "\n";
    }
}

void worker(int cpu_id)
{
    pin_thread(cpu_id);  // lock thread to CPU
    int i = cpu_id;

    while (true)
    {
        std::cout << "Thread #" << i << ": on CPU " << sched_getcpu() << "\n";
        // Simulate important work done by the thread by sleeping for a bit...
        std::this_thread::sleep_for(std::chrono::milliseconds(1));
    }
}

int main()
{
    std::jthread t1(worker, 0);
    std::jthread t2(worker, 1);
    std::jthread t3(worker, 2);
    std::jthread t4(worker, 3);
    std::jthread t5(worker, 4);
    std::jthread t6(worker, 5);
    std::jthread t7(worker, 6);
    std::jthread t8(worker, 7);
    std::jthread t9(worker, 8);
}