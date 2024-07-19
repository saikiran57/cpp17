/**
 * @file forward_reference.cpp
 * @author Saikiran Nadipilli
 * @brief
 * @date 2024-03-05
 *
 * @copyright Copyright (c) 2024
 *
 * https://en.cppreference.com/w/cpp/utility/forward
 */

/**
 * @brief It Forwards lvalues as either lvalues or as rvalues, depending on T.
 *
 * @tparam T
 * @param arg
 */
template <class T>
void wrapper(T&& arg)
{
    // arg is always lvalue
    foo(std::forward<T>(arg));  // Forward as lvalue or as rvalue, depending on T
}
