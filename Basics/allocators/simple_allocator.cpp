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

#include <iostream>
#include <memory>
#include <vector>

template <typename T>
class SimpleAllocator
{
public:
    using value_type = T;

    SimpleAllocator() = default;

    template <typename U>
    constexpr SimpleAllocator(const SimpleAllocator<U>&) noexcept
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

    void deallocate(T* p, std::size_t) noexcept
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

    friend bool operator==(const SimpleAllocator&, const SimpleAllocator&)
    {
        return true;
    }
    friend bool operator!=(const SimpleAllocator&, const SimpleAllocator&)
    {
        return false;
    }
};

int main()
{
    SimpleAllocator<int> alloc;

    std::vector<int, SimpleAllocator<int>> vec(alloc);

    std::cout << "Adding elements to vector:" << std::endl;
    vec.push_back(1);
    vec.push_back(2);
    vec.push_back(3);

    std::cout << "Vector contents: ";
    for (int i : vec)
    {
        std::cout << i << " ";
    }
    std::cout << std::endl;

    std::cout << "Resizing vector to 1 element:" << std::endl;
    vec.resize(1);

    std::cout << "Clearing vector:" << std::endl;
    vec.clear();

    return 0;
}