

#include <numeric>
#include <vector>

static constexpr auto use_vec()
{
    std::vector<int> temp{1, 2, 3, 4, 5};
    return temp;
}

static constexpr auto sum()
{
    const auto data = use_vec();

    return std::accumulate(data.begin(), data.end(), 0);
}

int main()
{
    constexpr auto val = sum();

    return val;
}