#include <chrono>
#include <cstddef>
#include <iostream>
#include <vector>

static constexpr size_t NUMBER_OF_ELEMENTS = 2'000'000'000;

int main()
{
    auto begin = std::chrono::system_clock::now();
    {
        std::vector<int> vec;
        // vec.reserve(NUMBER_OF_ELEMENTS); // very fast
        vec.resize(NUMBER_OF_ELEMENTS);  // very fast

        vec[1024] = 47;
        int const j = vec[1024];
        vec.push_back(23);
    }
    auto end = std::chrono::system_clock::now();

    std::cout << "duration seconds: " << std::chrono::duration_cast<std::chrono::seconds>(end - begin).count() << "\n";
}