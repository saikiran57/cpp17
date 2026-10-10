/**
 * @file thread_counter.cpp
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

class thread_counter
{
public:
    thread_counter(int from, int to) : counter(from), to(to) {}

    int get_next()
    {
        return counter++;
    }

    bool is_done()
    {
        return counter > to;
    }

private:
    int counter = 0;
    int to = 0;
};

void worker(int from, int to)
{
    thread_local thread_counter tc(from, to);

    while (!tc.is_done())
    {
        std::cout << "worker threadId: " << std::this_thread::get_id() << " value: " << tc.get_next() << "\n";
    }
}

int main()
{
    std::thread t1(worker, 0, 5000000);
    std::thread t2(worker, 10, 15);

    t1.join();
    t2.join();
}