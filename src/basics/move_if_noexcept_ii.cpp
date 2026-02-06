/**
 * @file move_if_noexcept_ii.cpp
 * @author Saikiran Nadipilli
 * @brief
 * @version 0.1
 * @date 2024-12-06
 *
 * @copyright Copyright (c) 2024
 *
 * @ref: https://www.learncpp.com/cpp-tutorial/stdmove_if_noexcept/
 *
 */

#include <exception>
#include <iostream>
#include <stdexcept>  // std::runtime_error
#include <utility>    // For std::pair, std::make_pair, std::move, std::move_if_noexcept

class MoveClass
{
private:
    int* m_mResource{};

public:
    MoveClass() = default;

    explicit MoveClass(int resource) : m_mResource{new int{resource}} {}

    // Copy constructor
    MoveClass(const MoveClass& that)
    {
        std::cout << "MoveClass copy constructor \n";
        // deep copy
        if (that.m_mResource != nullptr)
        {
            m_mResource = new int{*that.m_mResource};
        }
    }

    // Move constructor
    MoveClass(MoveClass&& that) noexcept : m_mResource{that.m_mResource}
    {
        std::cout << "MoveClass move constructor \n";
        that.m_mResource = nullptr;
    }

    ~MoveClass()
    {
        std::cout << "destroying " << *this << '\n';

        delete m_mResource;
    }

    friend std::ostream& operator<<(std::ostream& out, const MoveClass& moveClass)
    {
        out << "MoveClass(";

        if (moveClass.m_mResource == nullptr)
        {
            out << "empty";
        }
        else
        {
            out << *moveClass.m_mResource;
        }

        out << ')';

        return out;
    }
};

class CopyClass
{
public:
    bool m_mThrow{};

    CopyClass() = default;

    // Copy constructor throws an exception when copying from
    // a CopyClass object where its m_throw is 'true'
    CopyClass(const CopyClass& that) : m_mThrow{that.m_mThrow}
    {
        std::cout << "CopyClass copy constructor\n";
        if (m_mThrow)
        {
            throw std::runtime_error{"abort!"};
        }
    }
};

int main()
{
    // We can make a std::pair without any problems:
    std::pair my_pair{MoveClass{13}, CopyClass{}};

    std::cout << "my_pair.first: " << my_pair.first << '\n';

    // But the problem arises when we try to move that pair into another pair.
    try
    {
        my_pair.second.m_mThrow = true;  // To trigger copy constructor exception

        // The following line will throw an exception
        // std::pair moved_pair{std::move(my_pair)};  // We'll comment out this line later
        std::pair const moved_pair{std::move_if_noexcept(my_pair)};  // We'll uncomment this later

        std::cout << "moved pair exists\n";  // Never prints
    }
    catch (const std::exception& ex)
    {
        std::cerr << "Error found: " << ex.what() << '\n';
    }

    std::cout << "my_pair.first: " << my_pair.first << '\n';

    return 0;
}