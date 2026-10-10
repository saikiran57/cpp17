// #include <iostream>
// #include <string>
// #include <vector>
// #include <ranges>
// #include <chrono>
// #include <numeric>

// int main() {
//     std::cout << "=== REAL PERFORMANCE TEST ===\n\n";

//     constexpr int SIZE = 10'000'000;
//     std::vector<int> numbers(SIZE);
//     std::iota(numbers.begin(), numbers.end(), 0);

//     auto start = std::chrono::high_resolution_clock::now();

//     // TEST 1: Eager - multiple passes
//     std::vector<int> temp1;
//     for (int n : numbers) temp1.push_back(n * 2);

//     std::vector<int> temp2;
//     for (int n : temp1) temp2.push_back(n + 1);

//     std::vector<int> temp3;
//     for (int n : temp2) temp3.push_back(n / 2);

//     auto end = std::chrono::high_resolution_clock::now();
//     auto eager_time = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);

//     // TEST 2: Lazy - single pass
//     start = std::chrono::high_resolution_clock::now();

//     auto view = numbers
//         | std::views::transform([](int n) { return n * 2; })
//         | std::views::transform([](int n) { return n + 1; })
//         | std::views::transform([](int n) { return n / 2; });

//     std::vector<int> lazy_result;
//     for (int n : view) {
//         lazy_result.push_back(n);
//     }

//     end = std::chrono::high_resolution_clock::now();
//     auto lazy_time = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);

//     std::cout << "Eager (3 passes): " << eager_time.count() << "ms\n";
//     std::cout << "Lazy (1 pass): " << lazy_time.count() << "ms\n";
//     std::cout << "Lazy is " << (eager_time.count() * 100 / lazy_time.count())
//               << "% faster!\n";
// }

#include <algorithm>
#include <chrono>
#include <iostream>
#include <numeric>
#include <ranges>
#include <vector>

// For C++23, we can make it constexpr
#if __cplusplus >= 202302L
#include <array>
#endif

int main()
{
    std::cout << "=== REAL PERFORMANCE TEST ===\n\n";

    constexpr int SIZE = 50'000'000;

    // METHOD 1: Most efficient - direct initialization with reserve + iota
    std::cout << "1. Most efficient method:\n";
    auto start = std::chrono::high_resolution_clock::now();

    std::vector<int> numbers;
    numbers.reserve(SIZE);  // Pre-allocate memory (crucial for performance!)
    for (int i = 0; i < SIZE; ++i)
    {
        numbers.push_back(i);  // No reallocations due to reserve()
    }

    auto end = std::chrono::high_resolution_clock::now();
    auto time1 = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    std::cout << "  Time: " << time1.count() << "ms\n";

    // METHOD 2: Using iota (clear and efficient)
    std::cout << "2. Using iota (clear and efficient):\n";
    start = std::chrono::high_resolution_clock::now();

    std::vector<int> numbers2(SIZE);
    std::iota(numbers2.begin(), numbers2.end(), 0);  // Not constexpr, but efficient

    end = std::chrono::high_resolution_clock::now();
    auto time2 = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    std::cout << "  Time: " << time2.count() << "ms\n";

    // METHOD 3: Using generate (flexible but slightly slower)
    std::cout << "3. Using generate (flexible):\n";
    start = std::chrono::high_resolution_clock::now();

    std::vector<int> numbers3(SIZE);
    int n = 0;
    std::generate(numbers3.begin(), numbers3.end(), [&n]() {
        return n++;
    });

    end = std::chrono::high_resolution_clock::now();
    auto time3 = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    std::cout << "  Time: " << time3.count() << "ms\n";

    // METHOD 4: C++20 ranges (lazy, doesn't allocate yet!)
    std::cout << "4. C++20 ranges (lazy - no allocation yet):\n";
    start = std::chrono::high_resolution_clock::now();

    auto range = std::views::iota(0, SIZE);  // Lazy - doesn't create vector!

    end = std::chrono::high_resolution_clock::now();
    auto time4 = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    std::cout << "  Time: " << time4.count() << "µs (lazy!)\n";

    // Convert to vector when needed
    std::vector<int> numbers4(range.begin(), range.end());

// METHOD 5: C++23 constexpr array (compile-time if possible)
#if __cplusplus >= 202302L
    std::cout << "5. C++23 constexpr array (compile-time if possible):\n";
    start = std::chrono::high_resolution_clock::now();

    constexpr auto generate_array = []() constexpr {
        std::array<int, SIZE> arr{};
        for (int i = 0; i < SIZE; ++i)
        {
            arr[i] = i;
        }
        return arr;
    };
    constexpr auto arr = generate_array();  // Computed at compile time!
    std::vector<int> numbers5(arr.begin(), arr.end());

    end = std::chrono::high_resolution_clock::now();
    auto time5 = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    std::cout << "  Time: " << time5.count() << "µs (mostly compile-time)\n";
#endif

    std::cout << "\n=== Performance Comparison for Actual Operations ===\n";

    // Now test the actual transformations
    std::vector<int> numbers_test(SIZE);
    std::iota(numbers_test.begin(), numbers_test.end(), 0);

    // TEST 1: Eager - multiple passes
    std::cout << "\nEager (multiple passes):\n";
    start = std::chrono::high_resolution_clock::now();

    std::vector<int> temp1;
    temp1.reserve(SIZE);
    for (int n : numbers_test)
        temp1.push_back(n * 2);

    std::vector<int> temp2;
    temp2.reserve(SIZE);
    for (int n : temp1)
        temp2.push_back(n + 1);

    std::vector<int> temp3;
    temp3.reserve(SIZE);
    for (int n : temp2)
        temp3.push_back(n / 2);

    end = std::chrono::high_resolution_clock::now();
    auto eager_time = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    std::cout << "  Time: " << eager_time.count() << "ms\n";
    std::cout << "  Memory: ~" << (SIZE * sizeof(int) * 3 / 1024 / 1024) << "MB\n";

    // TEST 2: Optimized eager - single pass with caching
    std::cout << "\nOptimized Eager (single pass with caching):\n";
    start = std::chrono::high_resolution_clock::now();

    std::vector<int> optimized;
    optimized.reserve(SIZE);
    for (int n : numbers_test)
    {
        int val = n * 2;  // First op
        val = val + 1;    // Second op
        val = val / 2;    // Third op
        optimized.push_back(val);
    }

    end = std::chrono::high_resolution_clock::now();
    auto optimized_time = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    std::cout << "  Time: " << optimized_time.count() << "ms\n";
    std::cout << "  Memory: ~" << (SIZE * sizeof(int) / 1024 / 1024) << "MB\n";

    // TEST 3: Lazy (C++20 ranges) - single pass, no temporaries
    std::cout << "\nLazy (C++20 ranges):\n";
    start = std::chrono::high_resolution_clock::now();

    auto view = numbers_test | std::views::transform([](int n) {
                    return n * 2;
                })
                | std::views::transform([](int n) {
                      return n + 1;
                  })
                | std::views::transform([](int n) {
                      return n / 2;
                  });

    std::vector<int> lazy_result;
    lazy_result.reserve(SIZE);
    for (int n : view)
    {
        lazy_result.push_back(n);
    }

    end = std::chrono::high_resolution_clock::now();
    auto lazy_time = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    std::cout << "  Time: " << lazy_time.count() << "ms\n";
    std::cout << "  Memory: ~" << (SIZE * sizeof(int) / 1024 / 1024) << "MB\n";

    // Summary
    std::cout << "\n=== SUMMARY ===\n";
    std::cout << "Eager (3 passes):  " << eager_time.count() << "ms\n";
    std::cout << "Optimized eager:   " << optimized_time.count() << "ms\n";
    std::cout << "Lazy (ranges):     " << lazy_time.count() << "ms\n";
    std::cout << "Lazy is " << (eager_time.count() * 100 / std::max(lazy_time.count(), 1l))
              << "% faster than multi-pass eager\n";
}