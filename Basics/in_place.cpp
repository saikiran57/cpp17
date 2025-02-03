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

#include <iostream>
#include <optional>
#include <string>

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
    explicit UserName() : mName("Default")
    {
        std::cout << "UserName::UserName(\'";
        std::cout << mName << "\')\n";
    }

    explicit UserName(const std::string& str) : mName(str)
    {
        std::cout << "UserName::UserName(\'";
        std::cout << mName << "\')\n";
    }
    ~UserName()
    {
        std::cout << "UserName::~UserName(\'";
        std::cout << mName << "\')\n";
    }
    UserName(const UserName& u) : mName(u.mName)
    {
        std::cout << "UserName::UserName(copy \'";
        std::cout << mName << "\')\n";
    }
    UserName(UserName&& u) : mName(std::move(u.mName))
    {
        std::cout << "UserName::UserName(move \'";
        std::cout << mName << "\')\n";
    }
    UserName& operator=(const UserName& u)  // copy assignment
    {
        mName = u.mName;

        std::cout << "UserName::=(copy \'";
        std::cout << mName << "\')\n";

        return *this;
    }
    UserName& operator=(UserName&& u)  // move assignment
    {
        mName = std::move(u.mName);

        std::cout << "UserName::=(move \'";
        std::cout << mName << "\')\n";

        return *this;
    }

private:
    std::string mName;
};

int main()
{
    // std::optional<UserName> opt(UserName{});
    // std::optional<UserName> opt{std::in_place};
    auto opt = std::make_optional<UserName>();
}