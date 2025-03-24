#include <iostream>
#include <queue>

struct node
{
    int sum;
    int element;

    constexpr bool operator<(const node& r) const noexcept
    {
        return this->sum < r.sum;
    }
};

// std::less template specialization
// template <>
// struct std::less<node>
// {
//     constexpr bool operator()(const node &a, const node &b) const noexcept { return a.sum < b.sum; }
// };

// lambda function
auto customLess = [](node& l, node& r) {
    return l.sum < r.sum && l.element < r.element;
};

struct CustomLess
{
    constexpr bool operator()(const node& l, const node& r) const noexcept
    {
        return l.sum < r.sum;
    }
};

// void print_pq(std::priority_queue<node, std::vector<node>, decltype(customLess)>& pq)
// {
//     while(!pq.empty())
//     {
//         std::cout << "sum:" << pq.top().sum << " element:" << pq.top().element << "\n";
//         pq.pop();
//     }
// }

void print_pq(std::priority_queue<node>& pq)
{
    while (!pq.empty())
    {
        std::cout << "sum:" << pq.top().sum << " element:" << pq.top().element << "\n";
        pq.pop();
    }
}

int main()
{
    // std::priority_queue<node, std::vector<node>, decltype(customLess)> pq(customLess);
    std::priority_queue<node> pq;
    pq.push(node{1, 1});
    pq.push(node{4, 22});
    pq.push(node{5, 23});
    pq.push(node{5, 32});
    pq.push(node{6, 33});

    print_pq(pq);

    return 0;
}