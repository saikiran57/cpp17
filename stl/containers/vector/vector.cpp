/**
 * @file vector.cpp
 * @author Saikiran Nadipilli
 * @version 0.1
 * @date 2024-04-09
 *
 * @copyright Copyright (c) 2024
 *
 */

/**
 * @brief https://en.cppreference.com/w/cpp/container/vector/vector
 *
 * https://hackingcpp.com/cpp/std/vector.html
 *
 */

#include <algorithm>  // shuffle,
#include <iostream>
#include <numeric>
#include <random>  // mt19937
#include <string>
#include <vector>

namespace
{

class A
{
public:
    A()
    {
        std::cout << "default constructor\n";
    }
    explicit A(std::string other) noexcept : s(std::move(other))
    {
        std::cout << "parameterized move constructor\n";
    }
    // explicit A(std::string&& other) noexcept
    // {
    //     s = std::forward<std::string>(other);
    //     std::cout << "parameterized move constructor\n";
    // }
    A(const A& other) noexcept : s(other.s)
    {
        std::cout << "copy constructor\n";
    }
    A(A&& other) noexcept
    {
        s = std::move(other.s);
        std::cout << "move constructor\n";
    }
    A& operator=(const A& other) noexcept
    {
        if (this != &other)
        {
            s = other.s;
            std::cout << "copy assignment\n";
        }
        return *this;
    }
    A& operator=(A&& other) noexcept
    {
        if (this != &other)
        {
            s = std::move(other.s);
            std::cout << "move assignment\n";
        }
        return *this;
    }

    std::string value() const noexcept
    {
        return s;
    }

private:
    std::string s;
};

template <typename T>
std::ostream& operator<<(std::ostream& s, const std::vector<T> vec)
{
    s.put('{');
    char comma[]{'\0', ' ', '\0'};
    for (const auto& e : vec)
    {
        s << comma << e, comma[0] = ',';
    }
    return s << "}\n";
}

template <class ForwardIt, class T>
void iotat(ForwardIt first, ForwardIt last, T value)
{
    for (; first != last; ++first, ++value)
    {
        *first = value;
    }
}

}  // namespace

void construct_vector()
{
    std::cout << "\n------------- construct_vector() ----------------\n";
    // construct a new vector
    std::vector<int> vec1{1, 2, 3, 4, 5, 6};  // create a vector using initializer_list
    std::vector<int> const vec2(vec1.begin() + 3, vec1.end());
    std::vector<int> vec3(10);                             // create 10 elements holding 0
    std::vector<int> const vec4{100};                      // create 1 element holding 100
    std::vector<int> const vec5(10, 3);                    // create 10 elements holding 3
    std::vector<int> const deepCopyVec(vec1);              // Deep copy from vec1
    std::vector<std::string_view> vec6{"a", "bb", "ccc"};  // auto type deduction since c++17

    std::iota(vec3.begin(), vec3.end(), 0);  // increase vector element by 1

    std::cout << "vec1: " << vec1 << "vec2: " << vec2 << "vec3: " << vec3;

    // shallow copy vector
    std::vector<std::vector<int>::iterator> vec7(vec3.size());
    std::iota(vec7.begin(), vec7.end(), vec3.begin());

    // generate shuffle
    std::random_device rd;   // provide non deterministic random number
    std::mt19937 gen(rd());  // seeds mersenne twister engine
    std::shuffle(vec7.begin(), vec7.end(), gen);
    std::cout << "Contents of vec8, viewed via shuffled vec3:\n";
    vec3[0] = 99;  // since its a shallow copy if we change original vector it will reflect in vec7
    for (auto const i : vec7)
    {
        std::cout << " " << *i << ' ';
    }

    // insert elements in reverse order
    std::vector<int> vec8(vec1.rbegin(), vec1.rend());
    std::cout << "\nElements in reverse order: " << vec8;

    // we are moving data from one vector to other
    std::vector vec9(std::move(vec6));  // auto type deduction
    std::cout << "vec6: " << vec6 << "vec9: " << vec9;
}

/**
 * @brief insert and construct elements inplace using emplace and emplace_back
 *
 */
void insert_construct_elements_in_place()
{
    std::cout << "\n------------- insert_construct_elements_in_place() ----------------\n";
    std::vector<std::pair<std::string, int>> vec;

    // emplace_back will construct elements inplace and insert into back of the vector
    vec.emplace_back("one", 1);
    vec.emplace_back("two", 2);

    // construct element at a specific position using emplace method
    vec.emplace(vec.begin(), "zero", 0);

    std::cout << "vec: ";

    for (auto& [f, s] : vec)
    {
        std::cout << "{" << f << "," << s << "} ";
    }

    std::vector<A> vec1;
    vec1.reserve(10);

    A two{"two"};
    A three{"three"};

    vec1.emplace_back("one");
    vec1.emplace_back(two);
    vec1.emplace_back(std::move(three));

    std::cout << "vec1: ";

    for (auto& obj : vec1)
    {
        std::cout << obj.value() << " ";
    }
}

int main()
{
    construct_vector();

    insert_construct_elements_in_place();

    return 0;
}
