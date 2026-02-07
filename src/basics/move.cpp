// /**
//  * @file move.cpp
//  * @author Saikiran Nadipilli
//  * @brief
//  * @version 0.1
//  * @date 2024-12-06
//  *
//  * @copyright Copyright (c) 2024
//  *
//  */
// #include <iostream>
// #include <vector>
// #include <memory>
// #include <cassert>

// // template <typename T>
// // void foo(T &&arg)
// // {
// //   std::vector<int> var = arg;
// // }

// void foo(std::vector<int>&& arg)
// {
//     std::vector<int> vec2 = std::move(arg);
//     std::cout << "arg size: " << arg.size() << "\n";
//     std::cout << "vec2 size: " << vec2.size() << "\n";
// }

// void consume_v1(std::unique_ptr<int> p) {}
// void consume_v2(std::unique_ptr<int>&& p) {}

// void test_v1(){
//   auto x = std::make_unique<int>(5);
//   consume_v1(std::move(x));
//   assert(!x); // ok
// }

// void test_v2(){
//   auto x = std::make_unique<int>(5);
//   consume_v2(std::move(x));
//   //assert(!x); // fire!
//   std::cout << *x << std::endl;
// }

// int main()
// {
//     test_v1();
//     test_v2();
//     // std::vector<int> vec1(1'000'000, 1);
//     // foo(std::move(vec1));

//     // //std::vector<int> vec2 = std::move(vec1);

//     // std::cout << "vec1 size: " << vec1.size() << "\n";
//     return 0;
// }

#include <iostream>
#include <utility>
#include <vector>

using namespace std;

class DataHolder
{
public:
    // void setData(const vector<int>& data) { m_data = data; }
    // void setData(vector<int>&& data) { m_data = move(data); }
    void setData(vector<int> data)
    {
        m_mData = std::move(data);
    }

private:
    vector<int> m_mData;
};

int main()
{
    DataHolder wrapper;
    vector myData{11, 22, 33};
    wrapper.setData(std::move(myData));

    for (auto&& i : myData)
    {
        std::cout << i;
    }

    wrapper.setData({22, 33, 44});
}