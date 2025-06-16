
#include "custom_vector.hpp"

struct Bad
{
    Bad() {}
    Bad(Bad&&)  // may throw
    {
        std::cout << "Throwing move constructor called\n";
    }
    Bad(const Bad&)  // may throw as well
    {
        std::cout << "Throwing copy constructor called\n";
    }

    Bad& operator=(const Bad&)
    {
        std::cout << "Throwing copy assignment called\n";
        return *this;
    }
};

struct Good
{
    Good()
    {
        std::cout << "good constructor\n";
    }
    virtual ~Good()
    {
        std::cout << "good destructor\n";
    }
    Good(Good&&) noexcept  // will NOT throw
    {
        std::cout << "Non-throwing move constructor called\n";
    }
    Good(const Good&) noexcept  // will NOT throw
    {
        std::cout << "Non-throwing copy constructor called\n";
    }

    Good& operator=(const Good&) noexcept  // will NOT throw
    {
        std::cout << "Throwing copy assignment called\n";
        return *this;
    }

    Good& operator=(Good&& other) noexcept
    {
        if (this != &other)
        {
            std::cout << "Non throwing move assignment called\n";
        }
        return *this;
    }
};

#include <vector>

int main()
{
    // custom_vector<int> vec;

    // vec.push_back(123);
    // vec.push_back(321);
    // vec[0] = 1000;
    // // vec.pop_back();
    // vec.print();

    // custom_vector<std::string> vecstr;

    // vecstr.push_back("abc");
    // vecstr.push_back("bbc");

    // vecstr.print();

    // custom_vector<Bad> vecbad;

    // Bad bob;
    // vecbad.push_back(bob);
    // vecbad.push_back(Bad{});

    custom_vector<Good> vecgood;

    vecgood.push_back(Good{});
    // vecgood.push_back(Good{});

    return 0;
}