#include <functional>
#include <iostream>
#include <numeric>
#include <string>
#include <vector>

int main()
{
    std::vector<int> v{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

    int sum = std::accumulate(v.begin(), v.end(), 0);
    int product = std::accumulate(v.begin(), v.end(), 1, std::multiplies<int>());

    auto dash_fold = [](std::string a, int b) {
        return std::move(a) + "->" + std::to_string(b);
    };

    std::string s = std::accumulate(std::next(v.begin()), v.end(),
                                    std::to_string(v[0]),  // start with first element
                                    dash_fold);

    std::string tr = std::transform_reduce(
        std::next(v.begin()), v.end(), std::to_string(v[0]),
        [](std::string a, std::string b) {
            std::cout << "str: " << b << "\n";
            return std::move(a) + "->" + std::move(b);
        },
        [](int b) {
            std::cout << "int:" << b << "\n";
            return std::to_string(b);
        });

    // Right fold using reverse iterators
    std::string rs = std::accumulate(std::next(v.rbegin()), v.rend(),
                                     std::to_string(v.back()),  // start with last element
                                     dash_fold);

    std::cout << "sum: " << sum << '\n'
              << "product: " << product << '\n'
              << "dash-separated string: " << s << '\n'
              << "dash-separated string (right-folded): " << rs << '\n'
              << " reduce dash-separated string (right-folded): " << reduce << '\n'
              << "transform reduce dash-separated string (right-folded): " << tr << '\n';
}