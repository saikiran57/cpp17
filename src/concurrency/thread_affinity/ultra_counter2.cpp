#include <atomic>
#include <benchmark/benchmark.h>
#include <cstdint>
#include <iostream>
#include <pthread.h>
#include <sched.h>
#include <thread>
#include <vector>

class UltraCounter
{
    struct alignas(64) Slot
    {
        uint64_t value{0};  // Make it atomic for safe reads
    };

    std::vector<Slot> counters;
    std::atomic<int> next_cpu{0};
    const size_t cpu_count;

public:
    explicit UltraCounter(size_t cpu_count = std::thread::hardware_concurrency())
        : counters(cpu_count), cpu_count(cpu_count)
    {
    }

    static void set_thread_affinity(int cpu)
    {
        cpu_set_t set;
        CPU_ZERO(&set);
        CPU_SET(cpu, &set);
        pthread_setaffinity_np(pthread_self(), sizeof(cpu_set_t), &set);
    }

    int cpu_id()
    {
        thread_local int cpu = [&] {
            int cpu = next_cpu.fetch_add(1) % cpu_count;

            // set_thread_affinity(cpu);

            std::cout << "Assigned CPU: " << cpu << " thread: " << std::this_thread::get_id()
                      << " cpu: " << sched_getcpu() << "\n";

            return cpu;
        }();

        return cpu;
    }

    void increment() noexcept
    {
        counters[cpu_id()].value++;
    }

    void increment(int cpu_id) noexcept
    {
        counters[cpu_id].value++;
    }

    uint64_t read() const
    {
        uint64_t sum = 0;

        // Use acquire semantics to ensure we see all increments
        for (const auto& c : counters)
        {
            sum += c.value;
        }

        return sum;
    }
};

void with_thread_affinity()
{
    auto start = std::chrono::steady_clock::now();

    auto max_cpu = std::thread::hardware_concurrency();
    std::cout << "max cpu:" << max_cpu << "\n";
    UltraCounter counter(max_cpu);

    std::vector<std::thread> workers;

    for (size_t i = 0; i < max_cpu; i++)
    {
        workers.emplace_back([&] {
            auto cpu_id = counter.cpu_id();
            for (size_t j = 0; j < 50'000'000; j++)  //
                counter.increment(cpu_id);
        });
    }

    for (auto& t : workers)
        t.join();

    std::cout << "Total: " << counter.read() << std::endl;
    auto end = std::chrono::steady_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
    std::cout << "total duration: " << duration << " milliseconds\n";
}

// Thread affinity benchmark
static void thread_affinity(benchmark::State& s)
{
    for (auto _ : s)
    {
        with_thread_affinity();
    }
}

int main()
{
    with_thread_affinity();
    return 0;
}

// BENCHMARK(thread_affinity)->UseRealTime()->Unit(benchmark::kMillisecond);

// BENCHMARK_MAIN();
