#include <chrono>
#include <cstddef>
#include <iostream>
#include <type_traits>  // std::is_fundamental
#include <vector>

template <typename T>
class NoInit
{
    static_assert(std::is_fundamental_v<T>, "should be a fundamental type");

public:
    // constructor without initialization
    NoInit() noexcept = default;
    // implicit conversion T → no_init<T>
    constexpr NoInit(T value) noexcept : m_v{value} {}
    // implicit conversion no_init<T> → T
    constexpr operator T() const noexcept
    {
        return m_v;
    }

private:
    T m_v;
};

static constexpr size_t NUMBER_OF_ELEMENTS = 2'000'000'000;

int main()
{
    auto begin = std::chrono::system_clock::now();
    {
        std::vector<NoInit<int>> noInitVec;
        noInitVec.reserve(NUMBER_OF_ELEMENTS);  // fast - no init!
        noInitVec[1024] = 47;
        int j = noInitVec[1024];
        noInitVec.push_back(23);
    }
    auto end = std::chrono::system_clock::now();

    std::cout << "duration in seconds: " << std::chrono::duration_cast<std::chrono::seconds>(end - begin).count()
              << "\n";
}
