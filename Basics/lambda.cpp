/**
 * @file lambda.cpp
 * @author Saikiran Nadipilli
 * @brief
 * @version 0.1
 * @date 2024-10-14
 *
 * @copyright Copyright (c) 2024
 *
 */

#include <cstdint>
#include <functional>

namespace experiment
{

/**
 * @brief Function object performing comparison
 *
 * @tparam T
 */
template <typename T>
struct Gt
{
    constexpr bool operator()(const T& lhs, const T& rhs) const
    {
        return lhs > rhs;
    }
};

template <typename T = void>
struct Gt;

template <>
struct Gt<void>
{
    /**
     * @brief Test if lhs is greater then rhs
     *
     * @tparam T
     * @tparam U
     * @param lhs
     * @param rhs
     * @return true
     * @return false
     */
    template <class T, class U>
    constexpr bool operator()(T&& lhs, U&& rhs) const
    {
        return std::forward<T>(lhs) > std::forward<U>(rhs);
    }
};
}  // namespace experiment

static constexpr bool strictly_positive(int lhs)
{
    return std::greater<>()(lhs, 0);
}

int main()
{
    constexpr int a = 10;
    constexpr int b = 5;

    static_assert(experiment::Gt<int>()(a, b), "failed");
    static_assert(experiment::Gt<>()(a, 0), "failed");

    constexpr std::int64_t low = 0B1111;
    constexpr std::uint16_t high = 0X11;
    experiment::Gt<> const greater{};
    static_assert(greater(high, low));

    auto func = [](int a) constexpr {
        return experiment::Gt<>()(a, 0);
    };
}