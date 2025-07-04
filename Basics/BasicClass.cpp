#include <string>

/**
 * Basic class implementation
 */

class Basic
{
public:
    // constructor
    explicit Basic(int a, std::string str) : m_a(a), m_str(std::move(str)) {}

    // destructor
    ~Basic() = default;

    // copy constructor
    // copy assignment
    // move constructor
    // move assignment

    // operator overloading

    // friend function

    // static function

private:
    int m_a;
    std::string m_str;
};
