/**
 * @file crtp.hpp
 * @author Saikiran Nadipilli (saikirannadipilli@gmail.com)
 * @brief
 * @version 0.1
 * @date 2026-02-06
 *
 * @copyright Copyright (c) 2026
 *
 */

#pragma once

#include <type_traits>

/**
 * @brief Curiously recurring template pattern with compile-time type safety
 *
 * @tparam derived - Must be the actual derived class, not another type!
 */

template <typename derived>
class crtp_base
{
    static_assert(std::is_class_v<derived>, "CRTP Error: derived must be a class type.");

protected:
    crtp_base() = default;
    ~crtp_base() = default;

public:
    derived& impl() noexcept
    {
        return static_cast<derived&>(*this);
    }

    const derived& impl() const noexcept
    {
        return static_cast<const derived&>(*this);
    }
};
