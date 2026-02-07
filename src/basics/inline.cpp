/**
 * @file Inline.cpp
 * @author Saikiran Nadipilli
 * @brief https://en.cppreference.com/w/cpp/language/inline
 * @version 0.1
 * @date 2024-03-11
 *
 * @copyright Copyright (c) 2024
 *
 */

/**
 * @brief Inline variables
 *
 * https://www.learncpp.com/cpp-tutorial/sharing-global-constants-across-multiple-files-using-inline-variables/
 *
 * https://www.geeksforgeeks.org/cpp-17-inline-variables/
 *
 * In C++, inline functions are treated by default as having external linkage, meaning that the program behaves as
 * if there is only one copy of the function. The function will have the same address in all translation units and
 * each translation unit will share any static locals and string literals.
 *
 * Inline variables have external linkage by default, so that they are visible to the linker.
 * This is necessary so the linker can de-duplicate the definitions.
 *
 * Non-inline constexpr variables have internal linkage. If included into multiple translation units, each translation
 * unit will get its own copy of the variable. This is not an ODR violation because they are not exposed to the linker.
 *
 * Key Points:
 * Linkage:
 *
 * static gives internal linkage.
 * inline and constexpr default to external linkage unless combined with static.
 * Inlining:
 *
 * Only inline and static inline explicitly suggest inlining to the compiler, but modern compilers optimize inlining
 * independently. Compile-Time Evaluation:
 *
 * Only constexpr guarantees compile-time evaluation if possible.
 * Variables or return values of constexpr functions can be used in constant expressions.
 * Combining Keywords:
 *
 * static inline: Use for file-local optimizable helper functions.
 * static constexpr: Use for file-local constants or compile-time evaluated functions.
 */

namespace constants
{
inline constexpr auto PI{1.33333};
}

int main()
{
    static_assert(constants::PI == 1.33333);

    return 0;
}