/**
 * @file move_if_noexcept.cpp
 * @author Saikiran Nadipilli
 * @brief
 * @version 0.1
 * @date 2024-12-06
 *
 * @copyright Copyright (c) 2024
 *
 * @ref: https://en.cppreference.com/w/cpp/utility/move_if_noexcept
 */

#include <iostream>
#include <utility>

/**
 * @brief https://en.cppreference.com/w/cpp/types/is_move_constructible
 *
    Code Analysis
    Struct Definition:

    cpp
    Copy code
    struct Ex1
    {
        std::string str; // member has a non-trivial but non-throwing move constructor
    };
    std::string has a move constructor that is non-trivial because it involves dynamic memory management, but it is
 noexcept if the underlying allocator does not throw during operations. std::is_move_constructible_v<Ex1>:

    Checks if Ex1 is move-constructible.
    Since std::string is move-constructible and Ex1 only contains this member, Ex1 is also move-constructible.
    Result: true.
    std::is_trivially_move_constructible_v<Ex1>:

    Checks if Ex1's move constructor is trivial (doesn't perform any additional logic or require custom code).
    std::string has a non-trivial move constructor, so Ex1 cannot have a trivial move constructor.
    Result: false.
    std::is_nothrow_move_constructible_v<Ex1>:

    Checks if Ex1's move constructor is declared noexcept.
    Since std::string's move constructor is noexcept, Ex1's move constructor is also noexcept.
    Result: true.
    Static Assertions
    The static_assert statements verify these properties at compile time:

    std::is_move_constructible_v<Ex1>: Passed, as Ex1 is move-constructible.
    !std::is_trivially_move_constructible_v<Ex1>: Passed, as Ex1's move constructor is non-trivial.
    std::is_nothrow_move_constructible_v<Ex1>: Passed, as Ex1's move constructor is noexcept.
    Key Takeaways
    std::string is a powerful example of a type with a non-trivial but noexcept move constructor.
    The Ex1 struct inherits these properties because it contains std::string as its only member.
 */

struct Bad
{
    Bad() = default;
    Bad(Bad&& /*unused*/) noexcept  // may throw
    {
        std::cout << "Throwing move constructor called\n";
    }
    Bad(const Bad& /*unused*/)  // may throw as well
    {
        std::cout << "Throwing copy constructor called\n";
    }
};

struct Good
{
    Good() = default;
    Good(Good&& /*unused*/) noexcept  // will NOT throw
    {
        std::cout << "Non-throwing move constructor called\n";
    }
    Good(const Good& /*unused*/) noexcept  // will NOT throw
    {
        std::cout << "Non-throwing copy constructor called\n";
    }
};

int main()
{
    Good g;
    Bad b;
    [[maybe_unused]] Good const g2 = std::move_if_noexcept(g);
    [[maybe_unused]] Bad const b2 = std::move_if_noexcept(b);
}