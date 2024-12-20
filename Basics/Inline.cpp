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
 * Inline variables have external linkage by default, so that they are visible to the linker.
 * This is necessary so the linker can de-duplicate the definitions.
 *
 * Non-inline constexpr variables have internal linkage. If included into multiple translation units, each translation
 * unit will get its own copy of the variable. This is not an ODR violation because they are not exposed to the linker.
 */

#include <iostream>

namespace constants
{
inline constexpr auto PI{1.33333};
}

int main()
{
    static_assert(constants::PI == 1.33333);

    return 0;
}