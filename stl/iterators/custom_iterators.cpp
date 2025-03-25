#include <iostream>

template <typename T>
class RangeIterator
{
public:
    // Type that iterator refers to
    using t_ValueType = T;
    // Pointer
    using t_Pointer = T*;
    // Reference
    using t_Reference = T*;

    // Tag Indicates the iterator's capabilities
    using t_IteratorCategory = std::input_iterator_tag;

    // Type of difference between two iterators.
    using t_DifferenceType = int;

    explicit RangeIterator(T value) : mStep(0), m_value(value) {}

    RangeIterator(T value, T step) : mStep(step), m_value(value) {}

    // Dereference operator:
    t_ValueType& operator*()
    {
        return m_value;
    }

    // Dereference operator:
    const t_ValueType& operator*() const
    {
        return m_value;
    }

    t_ValueType* operator->()
    {
        return &m_value;
    }

    // Prefix increment operator
    RangeIterator& operator++()
    {
        m_value += mStep;
        return *this;
    }

    // Postfix increment operator
    RangeIterator& operator++(int)
    {
        m_value += mStep;
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
    T const mStep;
    T m_value;
};
