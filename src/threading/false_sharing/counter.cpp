#include <atomic>
#include <chrono>
#include <iostream>
#include <thread>
#include <vector>

// BAD - Subject to false sharing
struct BadCounter
{
    std::atomic<int> value{0};
};

// GOOD - No false sharing
struct alignas(64) GoodCounter
{
    std::atomic<int> value{0};
};

void test_false_sharing()
{
    const int iterations = 100'000'000;

    // These will be adjacent in memory
    BadCounter bad1, bad2;

    auto start = std::chrono::steady_clock::now();

    std::thread t1([&]() {
        for (int i = 0; i < iterations; i++)
        {
            bad1.value++;
        }
    });

    std::thread t2([&]() {
        for (int i = 0; i < iterations; i++)
        {
            bad2.value++;
        }
    });

    t1.join();
    t2.join();

    auto end = std::chrono::steady_clock::now();
    std::cout << "False sharing time: " << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count()
              << "ms\n";
}

void test_no_false_sharing()
{
    const int iterations = 100'000'000;

    // These will be on different cache lines
    GoodCounter good1, good2;

    auto start = std::chrono::steady_clock::now();

    std::thread t1([&]() {
        for (int i = 0; i < iterations; i++)
        {
            good1.value++;
        }
    });

    std::thread t2([&]() {
        for (int i = 0; i < iterations; i++)
        {
            good2.value++;
        }
    });

    t1.join();
    t2.join();

    auto end = std::chrono::steady_clock::now();
    std::cout << "No false sharing time: " << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count()
              << "ms\n";
}

int main()
{
    // test_false_sharing();

    test_no_false_sharing();
    return 0;
}
// Expected output (typical):
// False sharing time: 3683ms, 4162ms, 1383ms, 3486ms, 4029ms
// No false sharing time: 1100ms, 1754ms, 1378ms, 1100ms, 1126ms
// That's 4x slower with false sharing!