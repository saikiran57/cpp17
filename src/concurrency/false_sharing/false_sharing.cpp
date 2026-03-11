/**
 * @file false_sharing.cpp
 * @author Saikiran Nadipilli (saikirannadipilli@gmail.com)
 * @brief
 * @version 0.1
 * @date 2026-03-08
 *
 * @copyright Copyright (c) 2026
 *
 * @ref:
 * https://github.com/ITHelpDec/CPP-High-Performance/blob/f54fe8caafddb709765e576b89b2d78bef14e3a3/Chapter%2011%20-%20Concurrency/false_sharing.cpp
 *
 */

/**
 * When two or more threads access data (that isn't logically shared between threads), but happen to be located on the
 same cache line.
 * Can happen when using global data or dynamically-allocated data.
 * False sharing, or destructive interference, can degrade performance. It occurs when two
    threads use some data (that is not logically shared between the threads) but happen to be
    located in the same cache line. Imagine what would happen if the two threads are executing
    on different cores and constantly update the variable that resides on the shared cache line.
    The threads will invalidate the cache line for each other although there is no true sharing of
    data between the threads.

    False sharing will most likely occur when using global data or dynamically-allocated data
    that is shared between threads. An example where false sharing is likely to occur is when
    allocating an array that is shared between threads, but each thread is only using a single
    element of the array.

    The solution to this problem is to pad each element in the array so that two adjacent
    elements cannot reside on the same cache line. Since C++17, there is a portable way of doing
    this using the std::hardware_destructive_interference_size constant defined in
    <new> in combination with the alignas specifier. The following example demonstrates
    how to create an element that prevents false sharing:
    struct alignas(std::hardware_destructive_interference_size) Element {
    int counter_{};
    };

    auto elements = std::vector<Element>(num_threads);
    The elements in the vector are now guaranteed to reside on separate cache lines.
 */

#include <iostream>
#include <thread>
#include <vector>

struct Element
{
    int e = 42;
};

struct alignas(64) AlignedElement
{
    int e = 42;
};

template <typename E>
void printMemoryLocations(const std::vector<E>& evec)
{
    int i = 1;
    for (const auto& e : evec)
    {
        std::cout << i << ": " << &e << " (" << sizeof(e) << " bytes wide)\n";
        ++i;
    }
    std::cout << '\n';
}

int main()
{
    std::size_t num_threads = std::thread::hardware_concurrency();

    std::vector<Element> evec1(num_threads);
    std::vector<AlignedElement> evec2(num_threads);

    std::cout << "Element Vector\n";
    printMemoryLocations(evec1);

    std::cout << "AlignedElement Vector\n";
    printMemoryLocations(evec2);

    return 0;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// OUTPUT  - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

// Element Vector
// 1: 0x6000002052c0 (4 bytes)
// 2: 0x6000002052c4 (4 bytes)
// 3: 0x6000002052c8 (4 bytes)
// 4: 0x6000002052cc (4 bytes)
// 5: 0x6000002052d0 (4 bytes)
// 6: 0x6000002052d4 (4 bytes)
// 7: 0x6000002052d8 (4 bytes)
// 8: 0x6000002052dc (4 bytes)

// AlignedElement Vector
// 1: 0x1005044c0 (64 bytes)
// 2: 0x100504500 (64 bytes)
// 3: 0x100504540 (64 bytes)
// 4: 0x100504580 (64 bytes)
// 5: 0x1005045c0 (64 bytes)
// 6: 0x100504600 (64 bytes)
// 7: 0x100504640 (64 bytes)
// 8: 0x100504680 (64 bytes)

// Program ended with exit code: 0