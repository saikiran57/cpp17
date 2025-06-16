#include <iostream>
#include <queue>

struct Node
{
    int m_sum;
    int m_element;

    constexpr bool operator<(const Node& r) const noexcept
    {
        return this->m_sum < r.m_sum;
    }
};

// std::less template specialization
// template <>
// struct std::less<node>
// {
//     constexpr bool operator()(const node &a, const node &b) const noexcept { return a.sum < b.sum; }
// };

// lambda function
static auto customLess = [](Node& l, Node& r) {
    return l.m_sum < r.m_sum && l.m_element < r.m_element;
};

struct CustomLess
{
    constexpr bool operator()(const Node& l, const Node& r) const noexcept
    {
        return l.m_sum < r.m_sum;
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

static void print_pq(std::priority_queue<Node>& pq)
{
    while (!pq.empty())
    {
        std::cout << "sum:" << pq.top().m_sum << " element:" << pq.top().m_element << "\n";
        pq.pop();
    }
}

int main()
{
    // std::priority_queue<node, std::vector<node>, decltype(customLess)> pq(customLess);
    std::priority_queue<Node> pq;
    pq.push(Node{1, 1});
    pq.push(Node{4, 22});
    pq.push(Node{5, 23});
    pq.push(Node{5, 32});
    pq.push(Node{6, 33});

    print_pq(pq);

    return 0;
}