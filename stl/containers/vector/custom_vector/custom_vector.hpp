/**
 * @file custom_vector.hpp
 * @author Saikiran Nadipilli (saikirannadipilli@gmail.com)
 * @brief
 * @version 0.1
 * @date 2025-06-13
 *
 * @copyright Copyright (c) 2025
 *
 * @ref https://github.com/sigerror/fast-vector/tree/master
 *
 *
 */

/**
 * @brief Create custom generic vector
 *
 */

#pragma once

#include <cstdint>
#include <iostream>
#include <utility>

/**
 * @brief DEFAULT VECTOR CAPACITY
 *
 */
static constexpr int DEFAULT_VECTOR_CAPACITY = 0;

template <typename T>
class custom_vector
{
    using size_type = std::size_t;

public:
    custom_vector() = default;

    ~custom_vector() noexcept
    {
        if (m_array)
        {
            delete[] m_array;  // Deallocate memory
        }
    }

    custom_vector(int size) : m_size(size)
    {
        allocate(m_size);
    }

    custom_vector(const custom_vector& other) : m_size(other.m_size), m_capacity(other.m_capacity)
    {
        allocate(m_size);
        std::copy(other.m_array, other.m_array + m_size, m_array);
    }

    custom_vector& operator=(const custom_vector& other)
    {
        if (this != &other)
        {
            delete[] m_array;  // Deallocate current memory

            m_size = other.m_size;
            m_capacity = other.m_capacity;

            allocate(m_size);
            std::copy(other.m_array, other.m_array + m_size, m_array);
        }

        return *this;
    }

    void swap(custom_vector& other) noexcept
    {
        std::swap(m_size, other.m_size);
        std::swap(m_array, other.m_array);
        std::swap(m_capacity, other.m_capacity);
    }

    custom_vector(custom_vector&& other) noexcept
        : m_size(other.m_size), m_array(other.m_array), m_capacity(other.m_capacity)
    {
        other.m_size = 0;
        other.m_array = nullptr;
        other.m_capacity = 0;
    }

    custom_vector& operator=(custom_vector&& other) noexcept
    {
        if (this != &other)
        {
            delete[] m_array;  // Deallocate current memory

            m_size = other.m_size;
            m_array = other.m_array;
            m_capacity = other.m_capacity;

            other.m_size = 0;
            other.m_array = nullptr;
            other.m_capacity = 0;
        }

        return *this;
    }

    void push_back(const T& element)
    {
        static_assert(std::is_copy_constructible_v<T>, "Not copy construable");

        if (m_size * 2 == m_capacity)
        {
            reallocate();
        }

        m_array[m_size++] = element;
    }

    void push_back(T&& element)
    {
        static_assert(std::is_move_constructible_v<T>);

        if (m_size * 2 == m_capacity)
        {
            reallocate();
        }

        if (m_size == 0)
        {
            m_array = new T[]
        }

        m_array[m_size++] = std::forward<T>(element);
    }

    template <typename... Args>
    void emplace_back(Args&&... args)
    {
        if (m_size * 2 == m_capacity)
        {
            reallocate();
        }

        m_array[m_size++] = T(std::forward<Args>(args)...);
    }

    void pop_back()
    {
        if (m_size > 0)
        {
            if constexpr (!std::is_trivially_destructible_v<T>)
            {
                m_array[m_size - 1].~T();
                --m_size;
            }
        }
    }

    void allocate(std::uint32_t capacity)
    {
        m_array = new T[capacity];
    }

    void reserve(size_type size)
    {
        m_array = new T[size];
        m_size = size;
        m_capacity = size;
    }

    void reallocate()
    {
        m_capacity = m_growthFactor * m_capacity;

        auto temp = new T[m_capacity];

        for (size_t i = 0; i < m_size; i++)
        {
            // https://en.cppreference.com/w/cpp/utility/move_if_noexcept.html
            temp[i] = std::move_if_noexcept(m_array[i]);
        }

        delete[] m_array;

        m_array = temp;
    }

    void clear()
    {
        for (size_t i = 0; i < m_size; i++)
        {
            if constexpr (!std::is_trivially_destructible_v<T>)
            {
                m_array[i].~T();
            }
            else
            {
                m_array[i] = T();
            }
        }
        m_size = 0;
    }

    void print()
    {
        for (size_t i = 0; i < m_size; i++)
        {
            std::cout << m_array[i] << " ";
        }
    }

    T& operator[](int index)
    {
        if (index < 0 || index > m_size)
        {
            throw std::out_of_range("Index out of range");
        }

        return m_array[index];
    }

    T operator[](int index) const
    {
        if (index < 0 || index > m_size)
        {
            throw std::out_of_range("Index out of range");
        }

        return m_array[index];
    }

    constexpr size_type size() const
    {
        return m_size;
    }

    size_type capacity() const
    {
        return m_capacity;
    }

private:
    T* m_array;
    std::uint32_t m_size = 0;
    size_type m_growthFactor = 2;
    size_type m_capacity = DEFAULT_VECTOR_CAPACITY;
};
