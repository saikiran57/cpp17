/**
 * @file simple_simple_widget.hpp
 * @author Saikiran Nadipilli (saikirannadipilli@gmail.com)
 * @brief
 * @version 0.1
 * @date 2025-06-16
 *
 * @copyright Copyright (c) 2025
 *
 */
#pragma once

#include <iostream>

struct simple_widget
{
    simple_widget()
    {
        puts("simple_widget()");
    }
    ~simple_widget()
    {
        puts("~simple_widget()");
    }

    simple_widget(int)
    {
        puts("simple_widget(int)");
    }

    simple_widget(const simple_widget&)
    {
        puts("simple_widget(const simple_widget&)");
    }

    simple_widget& operator=(const simple_widget&)
    {
        puts("simple_widget& =operator(const simple_widget&)");
        return *this;
    }

    simple_widget(simple_widget&&) noexcept
    {
        puts("simple_widget(simple_widget&&)");
    }

    simple_widget& operator=(simple_widget&&) noexcept
    {
        puts("simple_widget& =operator(simple_widget&&)");
        return *this;
    }
};