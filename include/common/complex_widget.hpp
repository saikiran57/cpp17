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

class complex_widget
{
public:
    complex_widget()
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

    complex_widget(const complex_widget& other)
    {
        m_data = new int(*other.m_data);
        puts("complex_widget(const complex_widget&)");
    }

    complex_widget& operator=(const complex_widget& other)
    {
        puts("complex_widget& =operator(const complex_widget&)");
        if (this != &other)
        {
            delete m_data;
            m_data = new int(*other.m_data);
        }

        return *this;
    }

    complex_widget(complex_widget&& other) noexcept : m_data(other.m_data)
    {
        other.m_data = nullptr;
        puts("complex_widget(complex_widget&&)");
    }

    complex_widget& operator=(complex_widget&& other) noexcept
    {
        puts("complex_widget& =operator(complex_widget&&)");
        if (this != &other)
        {
            delete m_data;
            m_data = other.m_data;
            other.m_data = nullptr;
        }
        return *this;
    }

private:
    int* m_data = nullptr;
};