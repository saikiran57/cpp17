/**
 * @file set_basics.cpp
 * @author Saikiran Nadipilli (saikiran.n@arringo.com)
 * @brief
 * @version 0.1
 * @date 2025-03-23
 *
 * @copyright Copyright (c) 2025
 *
 */

#include <iostream>
#include <set>
#include <utility>
#include <vector>

int main()
{
    // set creation
    // By default set will be created in ascending order
    std::set<int> st;

    st.insert(3);
    st.insert(1);
    st.insert(2);

    for (auto v : st)
    {
        std::cout << v << "\n";
    }

    // create a pair set
    std::set<std::pair<int, int>> pairSet;

    pairSet.insert({3, 5});
    pairSet.insert({1, 100});
    pairSet.insert({2, 999});

    while (!pairSet.empty())
    {
        auto it = pairSet.begin();

        auto first = it->first;
        auto second = it->second;
        std::cout << first << "\n";
        pairSet.erase(it);
    }

    std::vector<std::vector<std::pair<int, int>>> adj(5);

    auto tep = adj[1];

    return 0;
}