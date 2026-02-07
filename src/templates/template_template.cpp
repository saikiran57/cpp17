/**
 * @file template_template.cpp
 * @author Saikiran Nadipilli
 * @brief
 * @version 0.1
 * @date 2025-04-07
 *
 * @copyright Copyright (c) 2025
 *
 */

#include <iostream>
#include <map>
#include <set>
#include <sstream>
#include <stack>
#include <string>
#include <vector>

template <typename T>  // primary template
class A
{
public:
    int x;
};

template <typename T>  // partial specialization
class A<T*>
{
public:
    long x;
};

// class template with a template template parameter V
template <template <typename> class V>
class C
{
public:
    V<int> y;   // uses the primary template
    V<int*> z;  // uses the partial specialization
};

int main()
{
    C<A> obj;
    obj.y.x = 100;
    obj.z.x = 200;

    std::stack<int> st;  // integer stack
    std::stack<double, std::vector<double>> stDouble;

    st.push(1);

    return 0;
}