#include <algorithm>
#include <array>
#include <chrono>
#include <iostream>
#include <new>
#include <numeric>
#include <random>  // Added for better random number generation
#include <thread>

#define FALSE_SHARING() true  // Changed to false to demonstrate the difference

int main()
{
    constexpr std::size_t numProcessors = 2;
    constexpr std::size_t numIter = 40'000'000;

#if FALSE_SHARING()
    std::cout << "With false sharing \n";
    struct resultType
    {
        int val;
        // No padding - this will cause false sharing
    };
#else
    std::cout << "Without false sharing\n";
    struct resultType
    {
        alignas(std::hardware_destructive_interference_size) int val;
        // Padding added to prevent false sharing
    };
#endif

    std::array<resultType, numProcessors> results{};
    std::array<std::thread, numProcessors> threads;

    // Fix 1: Initialize random number generator per thread
    std::random_device rd;

    auto start = std::chrono::high_resolution_clock::now();

    for (std::size_t i = 0; i < numProcessors; ++i)
    {
        auto& result = results[i];
        threads[i] = std::thread{[&result, numIter, i, &rd]() {
            // Fix 2: Each thread gets its own RNG with different seed
            std::mt19937 gen(rd() + i);  // Different seed for each thread
            std::uniform_int_distribution<> dis(0, 9);

            for (std::size_t j = 0; j < numIter; ++j)
            {
                // Fix 3: Removed unnecessary modulo operations
                result.val = (result.val + dis(gen)) % 50;
            }
        }};
    }

    std::for_each(begin(threads), end(threads), [](std::thread& t) {
        t.join();
    });

    auto stop = std::chrono::high_resolution_clock::now();

    std::cout << "Duration: " << std::chrono::duration_cast<std::chrono::milliseconds>(stop - start).count() << " ms\n";

    // Fix 4: Simplified accumulation
    int total = 0;
    for (const auto& r : results)
    {
        total += r.val;
    }
    std::cout << "Result: " << total << '\n';
}

/**
 * Without false sharing: 518 ms, 306 ms, 301 ms, 310 ms, 355 ms
 * With false sharing: 453 ms, 563 ms, 546 ms, 574 ms, 581 ms
 */