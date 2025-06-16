/**
 * @file Widges.cpp
 * @author Saikiran Nadipilli
 * @brief
 * @version 0.1
 * @date 2025-06-11
 *
 * @copyright Copyright (c) 2025
 *
 */

#include <charconv>  // for from_chars, to_chars
#include <iostream>
#include <string>
#include <type_traits>  // for std::remove_const_t

template <typename T>
class Widget
{
public:
    T x;  // In-class member initializer
    Widget() = default;
    Widget(T value) : x(value) {}
    ~Widget() = default;

    void set_x(T value)
    {
        x = value;
    }

    void SetX(T value)
    {
        x = value;
    }

    Widget& operator=(const Widget& other) = default;
};

// Multiplication operator between two Widget<T> types
template <typename T1, typename T2>
[[nodiscard]]
auto operator*(const Widget<T1>& lhs, const Widget<T2>& rhs)
{
    using ResultType = std::remove_const_t<decltype(lhs.x * rhs.x)>;
    Widget<ResultType> result;
    result.x = lhs.x * rhs.x;
    return result;
}

int main()
{
    Widget a{2};       // CTAD with int
    Widget b{2.0f};    // CTAD with float
    Widget c = a * b;  // Result should be Widget<float>

    std::cout << "c.x = " << c.x << '\n';
}
