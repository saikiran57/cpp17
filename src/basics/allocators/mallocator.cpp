

/*
 * @ref https://en.cppreference.com/w/cpp/named_req/Allocator.html
 */

#include <cstdlib>
#include <iostream>
#include <limits>
#include <new>
#include <vector>

template <class T>
struct Mallocator
{
    typedef T value_type;

    Mallocator() = default;

    template <class U>
    constexpr Mallocator(const Mallocator<U>&) noexcept
    {
    }

    [[nodiscard]] T* allocate(std::size_t n)
    {
        if (n > std::numeric_limits<std::size_t>::max() / sizeof(T)) throw std::bad_array_new_length();

        if (auto p = static_cast<T*>(std::malloc(n * sizeof(T))))
        {
            report(p, n);
            return p;
        }

        throw std::bad_alloc();
    }

    void deallocate(T* p, std::size_t n) noexcept
    {
        report(p, n, 0);
        std::free(p);
    }

private:
    void report(T* p, std::size_t n, bool alloc = true) const
    {
        std::cout << (alloc ? "Alloc: " : "Dealloc: ") << sizeof(T) * n << " bytes at " << std::hex << std::showbase
                  << reinterpret_cast<void*>(p) << std::dec << '\n';
    }
};

template <class T, class U>
bool operator==(const Mallocator<T>&, const Mallocator<U>&)
{
    return true;
}

template <class T, class U>
bool operator!=(const Mallocator<T>&, const Mallocator<U>&)
{
    return false;
}

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

struct simple_widget
{
    char* a;
};

int main()
{
    std::vector<complex_widget, Mallocator<complex_widget>> v;

    v.reserve(10);
    // std::cout << "capacity: " << v.capacity() << "\n";

    // v.emplace_back(43);
    // v.emplace_back(4);
    // v.emplace_back(43);
    // v.emplace_back(4);
    // v.emplace_back(43);
    // v.emplace_back(4);
    // v.emplace_back(43);
    // v.emplace_back(4);
    // v.emplace_back(43);
    // v.emplace_back(4);
}