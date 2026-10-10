/**
 * @file thread_affinity.cpp
 * @author Saikiran Nadipilli (saikirannadipilli@gmail.com)
 * @brief
 * @version 0.1
 * @date 2026-03-16
 *
 * @copyright Copyright (c) 2026
 * @ref https://eli.thegreenplace.net/2016/c11-threads-affinity-and-hyperthreading/
 */
#include <iostream>
#include <mutex>
#include <thread>
#include <vector>

// for thread affinity taskset -c 5,6 ./a.out this will run on thread 5,6

int main(int argc, const char** argv)
{
    constexpr unsigned num_threads = 4;
    // A mutex ensures orderly access to std::cout from multiple threads.
    std::mutex iomutex;
    std::vector<std::thread> threads(num_threads);
    for (unsigned i = 0; i < num_threads; ++i)
    {
        threads[i] = std::thread([&iomutex, i] {
            while (1)
            {
                {
                    // Use a lexical scope and lock_guard to safely lock the mutex only
                    // for the duration of std::cout usage.
                    std::lock_guard<std::mutex> iolock(iomutex);
                    std::cout << "Thread #" << i << ": on CPU " << sched_getcpu() << "\n";
                }

                // Simulate important work done by the thread by sleeping for a bit...
                std::this_thread::sleep_for(std::chrono::milliseconds(10));
            }
        });
    }

    for (auto& t : threads)
    {
        t.join();
    }
    return 0;
}