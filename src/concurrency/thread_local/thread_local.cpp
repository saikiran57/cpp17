/**
 * @file thread_local.cpp
 * @author Saikiran Nadipilli (saikirannadipilli@gmail.com)
 * @brief
 * @version 0.1
 * @date 2026-03-15
 *
 * @copyright Copyright (c) 2026
 *
 */

#include <iostream>
#include <thread>

using namespace std;

void thread_func(int from, int to)
{
    // thread_local for the counter that persists across recursions
    thread_local int counter = from;  // Initialized ONCE per thread with first from value

    if (counter > to) return;

    cout << "Thread ID: " << this_thread::get_id() << ", counter: " << counter << ", address: " << &counter << endl;

    counter++;
    thread_func(from, to);  // Note: from, to are PASSED but not used for initialization
}

int main()
{
    thread t1(thread_func, 0, 5);    // Works: first call initializes counter=0
    thread t2(thread_func, 10, 15);  // Works: first call initializes counter=10

    t1.join();
    t2.join();

    return 0;
}