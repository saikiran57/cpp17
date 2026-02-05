/**
 * @file packaged_task.cpp
 * @author Saikiran Nadipilli (saikirannadipilli@gmail.com)
 * @brief
 * @version 0.1
 * @date 2025-08-16
 *
 * @copyright Copyright (c) 2025
 *
 */

#include <future>
#include <iostream>
#include <thread>

/**
 * Packaged_task is class template its a wrapper around callable target, so that it can be invoked asynchronously
 *
 * It is similar to std::function but it returns std::future
 *
 */

// create package task

int func(int x, int y)
{
    return x + y;
}

void task_lambda()
{
    std::packaged_task<int(int, int)> task([](int x, int y) {
        return x + y;
    });

    auto result = task.get_future();

    task(2, 3);

    std::cout << "task lambda result: " << result.get() << "\n";
}

void task_thread()
{
    std::packaged_task<int(int, int)> task(func);

    auto result = task.get_future();

    std::thread worker(std::move(task), 2, 3);

    std::cout << "task thread result: " << result.get() << "\n";
    worker.join();
}

int main()
{
    task_lambda();
    task_thread();

    return 0;
}