/**
 * @file simple_allocator.cpp
 * @author Saikiran Nadipilli
 * @brief
 * @version 0.1
 * @date 2024-12-11
 *
 * @copyright Copyright (c) 2024
 *
 * https://godbolt.org/z/T7cE4MMbj
 */

#include <cstddef>
#include <iostream>
#include <memory>
#include <vector>

template <typename T>
class SimpleAllocator
{
public:
    using t_ValueType = T;

    SimpleAllocator() = default;

    template <typename U>
    constexpr explicit SimpleAllocator(const SimpleAllocator<U>& /*unused*/) noexcept
    {
    }

    T* allocate(std::size_t n)
    {
        std::cout << "Allocating " << n * sizeof(T) << " bytes" << std::endl;
        if (n > std::allocator_traits<SimpleAllocator>::max_size(*this))
        {
            throw std::bad_alloc();
        }
        return static_cast<T*>(::operator new(n * sizeof(T)));
    }

    void deallocate(T* p, std::size_t /*unused*/) noexcept
    {
        std::cout << "Deallocating memory" << std::endl;
        ::operator delete(p);
    }

    template <typename U, typename... Args>
    void construct(U* p, Args&&... args)
    {
        std::cout << "Constructing element" << std::endl;
        new (p) U(std::forward<Args>(args)...);
    }

    template <typename U>
    void destroy(U* p) noexcept
    {
        std::cout << "Destroying element" << std::endl;
        p->~U();
    }

    friend bool operator==(const SimpleAllocator& /*unused*/, const SimpleAllocator& /*unused*/)
    {
        return true;
    }
    friend bool operator!=(const SimpleAllocator& /*unused*/, const SimpleAllocator& /*unused*/)
    {
        return false;
    }
};

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

int main()
{
    SimpleAllocator<complex_widget> const alloc;
    std::vector<complex_widget, SimpleAllocator<complex_widget>> vec(alloc);

    // complex_widget w{1};
    // vec.push_back(w);
    // SimpleAllocator<int> const alloc;

    // std::vector<int, SimpleAllocator<int>> vec(alloc);

    // std::cout << "Adding elements to vector:" << std::endl;
    // vec.push_back(1);
    // vec.push_back(2);
    // vec.push_back(3);

    // std::cout << "Vector contents: ";
    // for (int i : vec)
    // {
    //     std::cout << i << " ";
    // }
    // std::cout << std::endl;

    // std::cout << "Resizing vector to 1 element:" << std::endl;
    // vec.resize(1);

    // std::cout << "Clearing vector:" << std::endl;
    // vec.clear();

    return 0;
}