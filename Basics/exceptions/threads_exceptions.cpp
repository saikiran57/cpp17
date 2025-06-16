/**
 * @file threads_exceptions.cpp
 * @author Saikiran Nadipilli (saikirannadipilli@gmail.com)
 * @brief
 * @version 0.1
 * @date 2025-06-11
 *
 * @copyright Copyright (c) 2025
 *
 */

#include <iostream>
#include <mutex>
#include <queue>
#include <thread>

void worker(int num, std::exception_ptr& ex)
{
    try
    {
        for (size_t i = 0; i < num; i++)
        {
            std::cout << "worker1:" << i << "\n";
            if (i == 10)
            {
                throw std::runtime_error{"worker1 exception"};
            }
        }
    }
    catch (...)
    {
        ex = std::current_exception();
    }
}

void single_thread()
{
    std::exception_ptr ex;
    std::thread t1(worker, 15, std::ref(ex));

    t1.join();

    if (ex)
    {
        try
        {
            std::rethrow_exception(ex);
        }
        catch (const std::exception& e)
        {
            std::cerr << e.what() << '\n';
        }
    }
}

class ExceptionalChannel
{
public:
    ExceptionalChannel() = default;

    void push(const std::exception_ptr& ex)
    {
        std::scoped_lock lk(mx);
        exceptionQueue.push(ex);
    }

    std::exception_ptr pop()
    {
        std::scoped_lock lk(mx);
        if (!exceptionQueue.empty())
        {
            auto ex = exceptionQueue.front();
            exceptionQueue.pop();

            return ex;
        }

        return nullptr;
    }

    void handle_exceptions()
    {
        while (!exceptionQueue.empty())
        {
            auto ex = pop();

            if (ex)
            {
                try
                {
                    std::rethrow_exception(ex);
                }
                catch (const std::exception& e)
                {
                    std::cerr << e.what() << '\n';
                }
            }
        }
    }

private:
    std::queue<std::exception_ptr> exceptionQueue;
    std::mutex mx;
};

void multiple_threads()
{
    auto worker1 = [](int num, ExceptionalChannel& ec) {
        try
        {
            for (size_t i = 0; i < num; i++)
            {
                std::cout << "worker1: " << i << "\n";

                if (i == 10)
                {
                    throw std::runtime_error{"worker1 exception"};
                }
            }
        }
        catch (...)
        {
            ec.push(std::current_exception());
        }
    };

    auto worker2 = [](int num, ExceptionalChannel& ec) {
        try
        {
            for (size_t i = 0; i < num; i++)
            {
                std::cout << "worker2: " << i << "\n";

                if (i == 15)
                {
                    throw std::runtime_error{"worker2 exception"};
                }
            }
        }
        catch (...)
        {
            ec.push(std::current_exception());
        }
    };

    auto worker3 = [](int num, ExceptionalChannel& ec) {
        try
        {
            for (size_t i = 0; i < num; i++)
            {
                std::cout << "worker3: " << i << "\n";

                if (i == 100)
                {
                    throw std::runtime_error{"worker3 exception"};
                }
            }
        }
        catch (...)
        {
            ec.push(std::current_exception());
        }
    };

    // std::exception_ptr ex;
    ExceptionalChannel ec;
    std::thread t1(worker1, 15, std::ref(ec));
    std::thread t2(worker2, 100, std::ref(ec));
    std::thread t3(worker3, 1000, std::ref(ec));

    t1.join();
    t2.join();
    t3.join();

    ec.handle_exceptions();
}

int main()
{
    // single_thread();

    multiple_threads();

    return 0;
}