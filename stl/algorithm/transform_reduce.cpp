/**
 * @file reduce_transform.cpp
 * @author Saikiran Nadipilli
 * @brief 
 * @version 0.1
 * @date 2024-05-19
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#include <iostream>
#include <vector>
#include <numeric>
#include <execution>

int main()
{
    std::vector<int> vec{1,2,3,4,5};
    std::vector<int> vec1{1,2,3,4,5};

    // default version
    auto dsum = std::transform_reduce(vec.begin(), vec.end(), 0, std::plus<>{}, [](int x){
        return x;
    });

    std::cout << "dsum:" << dsum << "\n"; 

    auto f = [](int x){
        return x*x;
    };

    auto sum = std::transform_reduce(vec.begin(), vec.end(), 0, std::plus<>{}, f); // 0+f(v0)+f(v1)...f(vn)=sum

    std::cout << "sum:" << sum << "\n"; 

    auto twoSum = std::transform_reduce(vec.begin(), vec.end(), vec1.begin(), 0); // std::plus, std::multiplies

     std::cout << "Twosum:" << twoSum << "\n"; 

    auto ptwoSum = std::transform_reduce(std::execution::par, vec.begin(), vec.end(), vec1.begin(), 0); // std::plus, std::multiplies

     std::cout << "PTwosum:" << ptwoSum << "\n"; 
}