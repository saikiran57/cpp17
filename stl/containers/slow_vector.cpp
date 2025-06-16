#include <chrono>
#include <cstddef>
#include <iostream>
#include <vector>

static constexpr size_t NUMBER_OF_ELEMENTS = 2'000'000'000;

int main()
{
    auto begin = std::chrono::system_clock::now();
    {
        std::vector<int> vec(NUMBER_OF_ELEMENTS);
        // vec.reserve(NUMBER_OF_ELEMENTS); // very fast
        // vec.resize(NUMBER_OF_ELEMENTS);  // very fast

        std::cout << "capacity:" << vec.capacity() << " size: " << vec.size() << "\n";

        vec[1024] = 47;
        int const j = vec[1024];
        vec.push_back(23);

        std::cout << "capacity:" << vec.capacity() << " size: " << vec.size() << "\n";
    }
    auto end = std::chrono::system_clock::now();

    std::cout << "duration microseconds: " << std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count()
              << "\n";
}