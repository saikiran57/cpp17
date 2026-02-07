#include <iostream>
#include <string>
#include <vector>

// TriviallyCopyable structure
struct MyStruct
{
    int m_n;
    double m_d;
};

struct MyStruct2
{
    int m_n{};
    double m_d{};
    std::string m_s;
};

int main()
{
    std::vector<MyStruct> const v1{{.m_n = 1, .m_d = 1.0}, {.m_n = 2, .m_d = 2.0}};
    std::vector<MyStruct> const v2{2};
    std::ranges::copy(v1, , v2.begin());  // calls memmove()

    for (const auto& o : v2)
    {
        std::cout << "After v2 copy, n:" << o.m_n << ", d:" << o.m_d << std::endl;
    }
    std::vector<MyStruct2> const v3{{.m_n = 1, .m_d = 1.0, .m_s = "Hello"}, {.m_n = 2, .m_d = 2.0, .m_s = "World"}};
    std::vector<MyStruct2> const v4{2};
    std::ranges::copy(v3, , v4.begin());  // Does not call memmove()

    for (const auto& o : v4)
    {
        std::cout << "After v4 copy, n:" << o.m_n << ", d:" << o.m_d << ", s:" << o.m_s << std::endl;
    }

    return 0;
}