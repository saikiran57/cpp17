/**
 * @file complex_widget.hpp
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
#include <utility>

class complex_widget
{
public:
    complex_widget() noexcept : m_data(nullptr)  // Explicit initialization
    {
        puts("complex_widget()");
    }

    ~complex_widget()
    {
        if (m_data)
        {
            delete m_data;
            puts("~complex_widget() memory deleted");
        }
        else
        {
            puts("~complex_widget() no memory deleted");
        }
    }

    complex_widget(int value) : m_data(new int(value))
    {
        puts("complex_widget(int)");
    }

    complex_widget(const complex_widget& other) : m_data(other.m_data ? new int(*other.m_data) : nullptr)
    {
        puts("complex_widget(const complex_widget&)");
    }

    complex_widget& operator=(const complex_widget& other)
    {
        puts("complex_widget& =operator(const complex_widget&)");
        if (this != &other)
        {
            // Exception-safe implementation
            int* new_data = other.m_data ? new int(*other.m_data) : nullptr;
            delete m_data;
            m_data = new_data;
        }
        return *this;
    }

    complex_widget(complex_widget&& other) noexcept : m_data(std::exchange(other.m_data, nullptr))
    {
        puts("complex_widget(complex_widget&&)");
    }

    complex_widget& operator=(complex_widget&& other) noexcept
    {
        puts("complex_widget& =operator(complex_widget&&)");
        if (this != &other)
        {
            delete m_data;
            m_data = std::exchange(other.m_data, nullptr);
        }
        return *this;
    }

    int get_value() const
    {
        if (!m_data)
        {
            throw std::runtime_error("Attempt to get value from null complex_widget");
        }
        return *m_data;
    }

    bool is_null() const noexcept
    {
        return m_data == nullptr;
    }

    friend std::ostream& operator<<(std::ostream& os, const complex_widget& w)
    {
        if (w.m_data)
        {
            os << "complex_widget(" << *w.m_data << ")";
        }
        else
        {
            os << "complex_widget(null)";
        }
        return os;
    }

private:
    int* m_data = nullptr;
};