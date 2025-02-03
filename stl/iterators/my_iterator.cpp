#include <algorithm>
#include <iostream>
#include <memory>
#include <random>
#include <vector>

template <typename T>
struct Iterator
{
    using iterator_category = typename std::vector<T>::iterator::iterator_category;
    using difference_type = typename std::vector<T>::iterator::difference_type;
    using value_type = typename std::vector<T>::iterator::value_type;
    using pointer = typename std::vector<T>::iterator::pointer;
    using reference = typename std::vector<T>::iterator::reference;

    Iterator() = default;

    explicit Iterator(typename std::vector<T>::iterator it, typename std::vector<T>::iterator realEnd) noexcept
        : it_(it), end_(realEnd)
    {
    }

    reference operator*() noexcept
    {
        return *it_;
    }
    pointer operator->() noexcept
    {
        return it_.operator->();
    }

    Iterator& operator++() noexcept
    {
        it_++;
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
        return a.it_ == b.it_ && a.end_ == b.end_;
    };

    // not needed in C++20... op rewrite rules
    friend bool operator!=(const Iterator& a, const Iterator& b)
    {
        return !(a == b);
    };

private:
    typename std::vector<T>::iterator end_;
    typename std::vector<T>::iterator it_;
};

template <typename T>
class MyVec
{
    using iterator = Iterator<T>;

public:
    MyVec() = default;
    MyVec(const std::vector<T>& vec) : data_(vec) {}

    size_t size() const
    {
        return data_.size();
    }

    iterator begin() noexcept
    {
        return iterator(data_.begin(), data_.end());
    }

    iterator end() noexcept
    {
        return iterator(data_.end(), data_.end());
    }

private:
    std::vector<T> data_;
};

int main()
{
    MyVec<int> vec{std::vector{1, 2, 3, 4}};

    for (auto& elem : vec)
        std::cout << elem << ", ";
}