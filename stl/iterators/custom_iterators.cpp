#include <iostream>

template<typename T>
class RangeIterator
{
public:
    // Type that iterator refers to
    using value_type = T;
    // Pointer
    using pointer = T*;
    // Reference
    using reference = T*;

    // Tag Indicates the iterator's capabilities
    using iterator_category = std::input_iterator_tag;

    // Type of difference between two iterators.
    using difference_type = int;

    RangeIterator(T value)
        : m_step(0), m_value(value)
    { }

    RangeIterator(T value, T step)
        : m_step(step), m_value(value)
    { }

    // Dereference operator:
    value_type& operator*() {
        return m_value;
    }

    // Dereference operator:
    const value_type&  operator*() const  {
        return m_value;
    }

    value_type* operator->() {
        return &m_value;
    }

    // Prefix increment operator
    RangeIterator& operator++() {
        m_value += m_step;
        return *this;
    }

    // Postfix increment operator
    RangeIterator& operator++(int) {
        m_value += m_step;
        return *this;
    }

    bool operator==(const RangeIterator& rhs) const
    {
        return this->m_value > rhs.m_value;
    }

    bool operator!=(const RangeIterator& rhs) const
    {
        return !this->operator==(rhs);
    }

private:
    T const m_step;
    T  m_value;
};