/**
 * @file ultra_counter.cpp
 * @author Saikiran Nadipilli (saikirannadipilli@gmail.com)
 * @brief
 * @version 0.1
 * @date 2026-03-16
 *
 * @copyright Copyright (c) 2026
 *
 */

#include <atomic>
#include <benchmark/benchmark.h>
#include <cstdint>
#include <iostream>
#include <thread>
#include <vector>

class UltraCounter
{
    struct alignas(64) Slot
    {
        uint64_t value = 0;
    };

    std::vector<Slot> counters;
    inline static std::atomic<int> next_cpu = 0;

public:
    explicit UltraCounter(size_t cpu_count = std::thread::hardware_concurrency()) : counters(cpu_count) {}

    static int cpu_id()
    {
        static unsigned int max_cpu = std::thread::hardware_concurrency();

        // thread_local int cpu = [&]{
        //     int cpu = next_cpu.fetch_add(1) % max_cpu;
        //     std::cout << "Assigned CPU: " << cpu << " thread: " << std::this_thread::get_id() << "cpu: " <<
        //     sched_getcpu()  << "\n"; return cpu;
        // }();

        thread_local int cpu = [&] {
            int cpu = next_cpu.fetch_add(1) % max_cpu;

            cpu_set_t set;
            CPU_ZERO(&set);
            CPU_SET(cpu, &set);

            pthread_setaffinity_np(pthread_self(), sizeof(cpu_set_t), &set);

            std::cout << "Assigned CPU: " << cpu << " thread: " << std::this_thread::get_id()
                      << " cpu: " << sched_getcpu() << "\n";

            return cpu;
        }();

        return cpu;
    }

    inline void increment() noexcept
    {
        counters[cpu_id()].value++;
    }

    uint64_t read() const
    {
        uint64_t sum = 0;

        for (const auto& c : counters)
            sum += c.value;

        return sum;
    }
};

void with_thread_affinity()
{
    auto start = std::chrono::steady_clock::now();

    auto max_cpu = std::thread::hardware_concurrency();
    UltraCounter counter(max_cpu);

    std::vector<std::thread> workers;

    for (size_t i = 0; i < max_cpu; i++)
    {
        workers.emplace_back([&] {
            for (size_t j = 0; j < 50'000'000; j++)  //
                counter.increment();
        });
    }

    for (auto& t : workers)
        t.join();

    std::cout << "Total: " << counter.read() << std::endl;
    auto end = std::chrono::steady_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
    std::cout << "total duration: " << duration << " milliseconds\n";
}

void without_thread_affinity()
{
    auto max_cpu = 4;  // std::thread::hardware_concurrency();
    UltraCounter counter(max_cpu);

    std::vector<std::thread> workers;

    for (size_t i = 0; i < max_cpu; i++)
    {
        workers.emplace_back([&] {
            for (size_t j = 0; j < 50'000'000; j++)  //
                counter.increment();
        });
    }

    for (auto& t : workers)
        t.join();

    std::cout << "Total: " << counter.read() << std::endl;
}

// Thread affinity benchmark
static void thread_affinity(benchmark::State& s)
{
    for (auto _ : s)
    {
        with_thread_affinity();
    }
}
BENCHMARK(thread_affinity)->UseRealTime()->Unit(benchmark::kMillisecond);

BENCHMARK_MAIN();

// int main()
// {
//     with_thread_affinity();
//     return 0;
// }
