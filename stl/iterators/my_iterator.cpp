#include <algorithm>
#include <iostream>
#include <memory>
#include <random>
#include <vector>

template <typename T>
struct Iterator
{
    using t_IteratorCategory = typename std::vector<T>::iterator::iterator_category;
    using t_DifferenceType = typename std::vector<T>::iterator::difference_type;
    using t_ValueType = typename std::vector<T>::iterator::value_type;
    using t_Pointer = typename std::vector<T>::iterator::pointer;
    using t_Reference = typename std::vector<T>::iterator::reference;

    Iterator() = default;

    explicit Iterator(typename std::vector<T>::iterator it, typename std::vector<T>::iterator realEnd) noexcept
        : m_it(it), m_end(realEnd)
    {
    }

    t_Reference operator*() noexcept
    {
        return *m_it;
    }
    t_Pointer operator->() noexcept
    {
        return m_it.operator->();
    }

    Iterator& operator++() noexcept
    {
        m_it++;
        return *this;
    }
    Iterator operator++(int) noexcept
    {
        auto tmp = *this;
        ++(*this);
        return tmp;
    }

    friend bool operator==(const Iterator& a, const Iterator& b) noexcept
    {
        return a.m_it == b.m_it && a.m_end == b.m_end;
    };

    // not needed in C++20... op rewrite rules
    friend bool operator!=(const Iterator& a, const Iterator& b)
    {
        return !(a == b);
    };

private:
    typename std::vector<T>::iterator m_end;
    typename std::vector<T>::iterator m_it;
};

template <typename T>
class MyVec
{
    using t_Iterator = Iterator<T>;

public:
    MyVec() = default;
    MyVec(const std::vector<T>& vec) : m_data(vec) {}

    size_t size() const
    {
        return m_data.size();
    }

    t_Iterator begin() noexcept
    {
        return t_Iterator(m_data.begin(), m_data.end());
    }

    t_Iterator end() noexcept
    {
        return t_Iterator(m_data.end(), m_data.end());
    }

private:
    std::vector<T> m_data;
};

int main()
{
    MyVec<int> vec{std::vector{1, 2, 3, 4}};

    for (auto& elem : vec)
        std::cout << elem << ", ";
}