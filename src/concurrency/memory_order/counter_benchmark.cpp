#include <atomic>
#include <iostream>
#include <thread>
#include <vector>

std::atomic<int> counter(0);

void worker_relaxed(int iterations)
{
    for (int i = 0; i < iterations; i++)
    {
        counter.fetch_add(1, std::memory_order_relaxed);
    }
}

void worker_seq_cst(int iterations)
{
    for (int i = 0; i < iterations; i++)
    {
        counter.fetch_add(1, std::memory_order_seq_cst);
    }
}

int main()
{
    const int THREADS = 4;
    const int ITERS_PER_THREAD = 10'000'000;

    std::vector<std::thread> threads;

    // Test relaxed
    auto start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < THREADS; i++)
    {
        threads.emplace_back(worker_relaxed, ITERS_PER_THREAD);
    }
    for (auto& t : threads)
        t.join();
    auto end = std::chrono::high_resolution_clock::now();

    std::cout << "Relaxed total: " << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count()
              << "ms\n";

    threads.clear();
    counter = 0;

    // Test seq_cst
    start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < THREADS; i++)
    {
        threads.emplace_back(worker_seq_cst, ITERS_PER_THREAD);
    }
    for (auto& t : threads)
        t.join();
    end = std::chrono::high_resolution_clock::now();

    std::cout << "Seq_cst total: " << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count()
              << "ms\n";

    return 0;
}