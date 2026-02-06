/**
 * @file in_place.cpp
 * @author Saikiran Nadipilli
 * @brief
 * @version 0.1
 * @date 2025-01-31
 *
 * @copyright Copyright (c) 2025
 *
 */

#include <cstddef>
#include <cstdlib>
#include <iostream>
#include <optional>
#include <string>
#include <utility>

/**
 * @brief https://www.cppstories.com/2018/07/in-place-cpp17/
 * https://coliru.stacked-crooked.com/a/00976d6c9c1b0c5f
 */

void* operator new(std::size_t count)
{
    std::cout << "allocating " << count << " bytes" << std::endl;
    return malloc(count);
}

void operator delete(void* ptr) noexcept
{
    std::cout << "global op delete called\n";
    std::free(ptr);
}

class UserName
{
public:
    explicit UserName() : m_mName("Default")
    {
        std::cout << "UserName::UserName(\'";
        std::cout << m_mName << "\')\n";
    }

    explicit UserName(std::string str) : m_mName(std::move(str))
    {
        std::cout << "UserName::UserName(\'";
        std::cout << m_mName << "\')\n";
    }
    ~UserName()
    {
        std::cout << "UserName::~UserName(\'";
        std::cout << m_mName << "\')\n";
    }
    UserName(const UserName& u) : m_mName(u.m_mName)
    {
        std::cout << "UserName::UserName(copy \'";
        std::cout << m_mName << "\')\n";
    }
    UserName(UserName&& u) noexcept : m_mName(std::move(u.m_mName))
    {
        std::cout << "UserName::UserName(move \'";
        std::cout << m_mName << "\')\n";
    }
    UserName& operator=(const UserName& u)  // copy assignment
    {
        m_mName = u.m_mName;

        std::cout << "UserName::=(copy \'";
        std::cout << m_mName << "\')\n";

        return *this;
    }
    UserName& operator=(UserName&& u) noexcept  // move assignment
    {
        m_mName = std::move(u.m_mName);

        std::cout << "UserName::=(move \'";
        std::cout << m_mName << "\')\n";

        return *this;
    }

private:
    std::string m_mName;
};

int main()
{
    // std::optional<UserName> opt(UserName{});
    // std::optional<UserName> opt{std::in_place};
    auto opt = std::make_optional<UserName>();
}