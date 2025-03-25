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

#include <cstddef>
#include <string>
#if PARALLEL
#include <execution>
#define PAR std::execution::par,
#else
#define PAR
#endif

#include <algorithm>
#include <functional>
#include <iostream>
#include <iterator>
#include <numeric>
#include <vector>

/**
 * @brief https://en.cppreference.com/w/cpp/algorithm/transform_reduce
 *
 * @return int
 */

// to parallelize non-associate accumulative operation, you'd better choose
// transform_reduce instead of reduce; e.g., a + b * b != b + a * a
static void print_sum_squared(long const num)
{
    // std::cout.imbue(std::locale{"en_US.UTF8"});
    std::cout << "num = " << num << '\n';

    // create an immutable vector filled with pattern: 1,2,3,4, 1,2,3,4 ...
    const std::vector<long> v{[n = num * 4] {
        std::vector<long> v;
        v.reserve(n);
        std::generate_n(std::back_inserter(v), n, [i = 0]() mutable {
            return 1 + (i++ % 4);
        });
        return v;
    }()};

    auto squared_sum = [](auto sum, auto val) {
        return sum + (val * val);
    };

    auto sum1 = std::accumulate(v.cbegin(), v.cend(), 0L, squared_sum);
    std::cout << "accumulate(): " << sum1 << '\n';

    auto sum2 = std::reduce(PAR v.cbegin(), v.cend(), 0L, squared_sum);
    std::cout << "reduce(): " << sum2 << '\n';

    auto sum3 = std::transform_reduce(PAR v.cbegin(), v.cend(), 0L, std::plus{}, [](auto val) {
        return val * val;
    });
    std::cout << "transform_reduce(): " << sum3 << "\n\n";
}

int main()
{
    std::vector<int> vec{1, 2, 3, 4, 5};
    std::vector<int> vec1{1, 2, 3, 4, 5};

    // default version
    auto dsum = std::transform_reduce(vec.begin(), vec.end(), 0, std::plus<>{}, [](int x) {
        return x;
    });

    std::cout << "dsum:" << dsum << "\n";

    auto f = [](int x) {
        return x * x;
    };

    auto sum = std::transform_reduce(vec.begin(), vec.end(), 0, std::plus<>{}, f);  // 0+f(v0)+f(v1)...f(vn)=sum

    std::cout << "sum:" << sum << "\n";

    auto twoSum = std::transform_reduce(vec.begin(), vec.end(), vec1.begin(), 0);  // std::plus, std::multiplies

    std::cout << "Twosum:" << twoSum << "\n";

    auto ptwoSum = std::transform_reduce(PAR vec.begin(), vec.end(), vec1.begin(),
                                         0);  // std::plus, std::multiplies

    std::cout << "PTwosum:" << ptwoSum << "\n";

    auto mice = std::vector<std::string>{"Mickey", "Minnie", "Jerry"};
    auto num_chars = std::transform_reduce(
        mice.begin(), mice.end(), size_t{0},
        [](size_t a, size_t b) {
            return a + b;
        },  // Reduce
        [](const std::string& m) {
            return m.size();
        }  // Transform
    );
    // num_chars is 17
    std::cout << "num_chars: " << num_chars << "\n\n";

    print_sum_squared(1);
    print_sum_squared(1'000);
    print_sum_squared(1'000'000);
}
