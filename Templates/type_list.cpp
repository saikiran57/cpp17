/**
 * @file type_list.cpp
 * @author Saikiran Nadipilli
 * @brief
 * @version 0.1
 * @date 2025-01-31
 *
 * @copyright Copyright (c) 2025
 *
 */

#include <cstddef>
#include <iostream>
#include <type_traits>
#include <variant>

// // Type alias for ID representation
// using id_type = int;

// template <typename... Ts>
// class TypeList;

// // Concept to check for repeated types using fold expressions
// template <typename... Ts>
// concept NoRepeatedTypes = (!(std::is_same_v<Ts, Ts> || ...)) && true;

// // Base case for empty TypeList
// template <>
// class TypeList<> {
// public:
//     static constexpr id_type id = -1;

//     template <typename>
//     static constexpr id_type index_of() { return id; }
// };

// // Main TypeList implementation with concept enforcement
// template <typename T, typename... Ts>
// requires NoRepeatedTypes<T, Ts...>
// class TypeList<T, Ts...> {
//     using remaining_types = TypeList<Ts...>;
//     static constexpr id_type id = sizeof...(Ts);

// public:
//     template <typename U>
//     static constexpr id_type index_of() {
//         if constexpr (std::is_same_v<T, U>) {
//             return id;
//         } else {
//             return remaining_types::template index_of<U>();
//         }
//     }
// };

template <typename T, typename... Types>
constexpr bool are_types_unique_v = (!std::is_same_v<T, Types> && ...) && are_types_unique_v<Types...>;

template <typename T>
constexpr bool are_types_unique_v<T> = true;

int main()
{
    std::variant<int, int> vec{std::in_place_index<1>, 34};
    vec.emplace<0>(1);
    static_assert(are_types_unique_v<int, float, double, char>);

    return 0;
}