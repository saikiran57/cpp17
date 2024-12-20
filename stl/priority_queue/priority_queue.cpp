/**
 * @file priority_queue.cpp
 * @author Saikiran Nadipilli
 * @brief
 * @version 0.1
 * @date 2024-10-16
 *
 * @copyright Copyright (c) 2024
 *
 */

/**
 * @brief https://en.cppreference.com/w/cpp/container/priority_queue
 *
 * https://www.geeksforgeeks.org/priority-queue-in-cpp-stl/
 *
 */

#include <iostream>
#include <queue>

template <typename T>
void pop_println(std::string_view rem, T& pq)
{
    std::cout << rem << ": ";
    for (; !pq.empty(); pq.pop())
        std::cout << pq.top() << ' ';
    std::cout << '\n';
}

void max_heap(std::vector<int>& data)
{
    // direct construction
    std::priority_queue<int> maxHeap(data.begin(), data.end());
    pop_println("max heap", maxHeap);

    std::priority_queue<int> maxHeap2(std::less<int>(), data);
    pop_println("max heap2", maxHeap2);

    // custom lambda comparator less
    auto cmp = [](int a, int b) {
        return a < b;
    };

    std::priority_queue<int, std::vector<int>, decltype(cmp)> maxHeap3(cmp, data);
    pop_println("max heap3", maxHeap3);

    // custom function object comparator
    struct customLess
    {
        bool operator()(int a, int b)
        {
            return a < b;
        }
    };

    std::priority_queue maxHeap4(data.begin(), data.end(), customLess{});
    pop_println("max heap4", maxHeap4);
}

void min_heap(std::vector<int>& data)
{
    std::priority_queue<int, std::vector<int>, std::greater<int>> minHeap(std::greater<int>(), data);
    pop_println("min heap", minHeap);
}

int main()
{
    std::vector<int> data{3, 1, 4, 2, 5, 6, 7, 10, 9, 8};
    // max_heap()
    max_heap(data);

    // min_heap()
    std::cout << "------------ Min heap-------------\n";
    min_heap(data);

    return 0;
}
