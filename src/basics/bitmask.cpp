/**
 * @file bitmask.cpp
 * @author Saikiran Nadipilli (saikirannadipilli@gmail.com)
 * @brief
 * @version 0.1
 * @date 2026-02-10
 *
 * @copyright Copyright (c) 2026
 *
 */

#include <iostream>
#include <type_traits>

template <typename T>
concept scoped_enum = std::is_scoped_enum_v<T>;

template <scoped_enum e>
constexpr e operator|(e lhs, e rhs)
{
    using U = std::underlying_type_t<e>;
    return static_cast<e>(static_cast<U>(lhs) | static_cast<U>(rhs));
}

template <scoped_enum e>
constexpr e operator&(e lhs, e rhs)
{
    using U = std::underlying_type_t<e>;
    return static_cast<e>(static_cast<U>(lhs) & static_cast<U>(rhs));
}

template <scoped_enum e>
constexpr e operator^(e lhs, e rhs)
{
    using U = std::underlying_type_t<e>;
    return static_cast<e>(static_cast<U>(lhs) ^ static_cast<U>(rhs));
}

enum class Flags : int
{
    READ,
    WRITE,
    MODIFY,
    DELETE,
    RENAME
};

int main()
{
    Flags flags;
    flags = Flags::READ | Flags::WRITE | Flags::MODIFY;

    std::cout << "flags: " << static_cast<int>(flags) << "\n";
}