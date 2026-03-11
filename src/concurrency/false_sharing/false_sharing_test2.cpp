// Understanding False Sharing in C++

#include <chrono>
#include <iostream>
#include <thread>
#include <vector>

constexpr int NUM_THREADS = 4;
constexpr long long ARRAY_SIZE = 1000000;

// Create array with padding to prevent false sharing
struct alignas(64) Data
{
    int value;
    char padding[64 - sizeof(int)];
};

Data data[ARRAY_SIZE];

// Function to be executed by each thread
void increment(int id)
{
    for (int i = id; i < ARRAY_SIZE; i += NUM_THREADS)
    {
        data[i].value++;
    }
}

int main()
{
    std::vector<std::thread> threads(NUM_THREADS);

    // Record start time
    auto start_time = std::chrono::high_resolution_clock::now();

    // Create threads
    for (int i = 0; i < NUM_THREADS; i++)
    {
        threads[i] = std::thread(increment, i);
    }

    // Wait for threads to complete
    for (int i = 0; i < NUM_THREADS; i++)
    {
        threads[i].join();
    }

    // Record end time
    auto end_time = std::chrono::high_resolution_clock::now();

    // Calculate duration
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time);

    // Print execution time
    std::cout << "Execution time: " << duration.count() << " microseconds" << std::endl;

    // Print only a few values to avoid overwhelming output
    std::cout << "\nFirst 10 values:" << std::endl;
    for (int i = 0; i < std::min(10LL, ARRAY_SIZE); i++)
    {
        std::cout << "Data[" << i << "].value = " << data[i].value << std::endl;
    }

    // Print verification
    std::cout << "\nExpected increment per element: " << 1 << std::endl;

    // Optional: Verify that all increments were correct
    bool all_correct = true;
    for (int i = 0; i < ARRAY_SIZE; i++)
    {
        if (data[i].value != 1)
        {
            all_correct = false;
            break;
        }
    }

    if (all_correct)
    {
        std::cout << "All values correctly incremented!" << std::endl;
    }
    else
    {
        std::cout << "Warning: Some values were not incremented correctly!" << std::endl;
    }

    return 0;
}