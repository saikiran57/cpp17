#include <array>  // For std::array
#include <iostream>
#include <numeric>  // For std::accumulate

constexpr int sum_elements()
{
    constexpr std::array<int, 5> data = {1, 2, 3, 4, 5};
    return std::accumulate(data.begin(), data.end(), 0);  // Sum all elements starting with 0
}

int main()
{
    constexpr int result = sum_elements();

    static_assert(result == 15, "not a valid data");

    // The result is known at compile-time
    std::cout << "Sum: " << result << '\n';
    return result;
}