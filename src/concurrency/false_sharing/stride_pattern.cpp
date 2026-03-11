#include <chrono>
#include <iostream>
#include <thread>
#include <vector>

constexpr int NUM_THREADS = 4;
constexpr long long ARRAY_SIZE = 5000000;

// Create array with false sharing
struct Data
{
    // alignas(64) int value;
    int value;
};

Data data[ARRAY_SIZE];

void increment_with_stride(int id, int stride)
{
    for (int i = id; i < ARRAY_SIZE; i += stride)
    {
        data[i].value++;
    }
}

int main()
{
    // Test different stride values
    std::vector<int> strides = {1, 4, 16, 64, 256};
    for (int stride : strides)
    {
        auto start = std::chrono::high_resolution_clock::now();

        std::vector<std::thread> threads;
        for (int i = 0; i < NUM_THREADS; i++)
        {
            threads.emplace_back(increment_with_stride, i, stride);
        }

        for (auto& t : threads)
            t.join();

        auto end = std::chrono::high_resolution_clock::now();
        auto ms = std::chrono::duration_cast<std::chrono::microseconds>(end - start);

        std::cout << "Stride " << stride << ": " << ms.count() << " us\n";
    }
}