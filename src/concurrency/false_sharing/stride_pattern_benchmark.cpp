#include <algorithm>
#include <chrono>
#include <iomanip>
#include <iostream>
#include <numeric>
#include <thread>
#include <vector>

constexpr int NUM_THREADS = 4;
constexpr long long ARRAY_SIZE = 5'000'000;
constexpr int NUM_ITERATIONS = 10;

struct DataNoPadding
{
    int value = 0;
};

struct alignas(64) DataWithPadding
{
    int value = 0;
};

template <typename T>
void increment_with_stride(T* data, int tid, int stride)
{
    const long long block = stride * NUM_THREADS;

    for (long long base = tid * stride; base < ARRAY_SIZE; base += block)
    {
        long long end = std::min(base + stride, ARRAY_SIZE);

        for (long long i = base; i < end; ++i)
        {
            data[i].value++;
        }
    }
}

template <typename T>
void reset_data(std::vector<T>& data)
{
    for (auto& e : data)
        e.value = 0;
}

template <typename T>
bool verify_data(const std::vector<T>& data)
{
    for (const auto& e : data)
    {
        if (e.value != 1) return false;
    }
    return true;
}

struct Result
{
    double mean;
    double min;
    double max;
};

template <typename T>
Result run_benchmark(std::vector<T>& data, int stride)
{
    std::vector<double> times;
    times.reserve(NUM_ITERATIONS);

    for (int iter = 0; iter < NUM_ITERATIONS; iter++)
    {
        reset_data(data);

        auto start = std::chrono::high_resolution_clock::now();

        std::vector<std::thread> threads;
        threads.reserve(NUM_THREADS);

        for (int t = 0; t < NUM_THREADS; t++)
        {
            threads.emplace_back(increment_with_stride<T>, data.data(), t, stride);
        }

        for (auto& th : threads)
            th.join();

        auto end = std::chrono::high_resolution_clock::now();

        double ms = std::chrono::duration<double, std::milli>(end - start).count();

        times.push_back(ms);

        if (!verify_data(data))
        {
            std::cout << "Verification failed!\n";
        }
    }

    double mean = std::accumulate(times.begin(), times.end(), 0.0) / times.size();

    double min = *std::min_element(times.begin(), times.end());
    double max = *std::max_element(times.begin(), times.end());

    return {mean, min, max};
}

int main()
{
    std::cout << std::fixed << std::setprecision(2);

    std::vector<int> strides = {1, 2, 4, 8, 16, 32, 64, 128, 256, 512, 1024, 2048, 4096, 8192};

    std::vector<DataNoPadding> data_no_pad(ARRAY_SIZE);
    std::vector<DataWithPadding> data_pad(ARRAY_SIZE);

    std::cout << "===== Stride False Sharing Benchmark =====\n\n";
    std::cout << "Threads: " << NUM_THREADS << "\n";
    std::cout << "Array size: " << ARRAY_SIZE << "\n\n";

    std::cout << std::left << std::setw(10) << "Stride" << std::setw(15) << "NoPad(ms)" << std::setw(15) << "Pad(ms)"
              << "Ratio\n";

    std::cout << "---------------------------------------------\n";

    for (auto stride : strides)
    {
        auto r1 = run_benchmark(data_no_pad, stride);
        auto r2 = run_benchmark(data_pad, stride);

        double ratio = r1.mean / r2.mean;

        std::cout << std::setw(10) << stride << std::setw(15) << r1.mean << std::setw(15) << r2.mean << ratio << "\n";
    }

    double mem_no_pad = (ARRAY_SIZE * sizeof(DataNoPadding)) / (1024.0 * 1024.0);

    double mem_pad = (ARRAY_SIZE * sizeof(DataWithPadding)) / (1024.0 * 1024.0);

    std::cout << "\nMemory usage\n";
    std::cout << "No padding: " << mem_no_pad << " MB\n";
    std::cout << "With padding: " << mem_pad << " MB\n";

    return 0;
}