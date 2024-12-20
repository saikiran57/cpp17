#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

// TriviallyCopyable structure
struct MyStruct
{
    int n;
    double d;
};

struct MyStruct2
{
    int n;
    double d;
    std::string s;
};

int main()
{
    std::vector<MyStruct> v1{{1, 1.0}, {2, 2.0}};
    std::vector<MyStruct> v2{2};
    std::copy(v1.begin(), v1.end(), v2.begin());  // calls memmove()

    for (const auto& o : v2)
    {
        std::cout << "After v2 copy, n:" << o.n << ", d:" << o.d << std::endl;
    }
    std::vector<MyStruct2> v3{{1, 1.0, "Hello"}, {2, 2.0, "World"}};
    std::vector<MyStruct2> v4{2};
    std::copy(v3.begin(), v3.end(), v4.begin());  // Does not call memmove()

    for (const auto& o : v4)
    {
        std::cout << "After v4 copy, n:" << o.n << ", d:" << o.d << ", s:" << o.s << std::endl;
    }

    return 0;
}