/**
 * @file variant_II.cpp
 * @author Saikiran Nadipilli (saikirannadipilli@gmail.com)
 * @brief
 * @version 0.1
 * @date 2026-02-22
 *
 * @copyright Copyright (c) 2026
 *
 */

#include <iostream>
#include <type_traits>
#include <variant>

using VariantType = std::variant<int, bool, std::string>;

int main()
{
    VariantType var = true;

    std::visit(
        [](auto& arg) {
            using T = decltype(arg);
            if constexpr (std::is_same_v<T, int>)
            {
                std::cout << "integer\n";
            }
            std::cout << arg << "\n";
        },
        var);
}