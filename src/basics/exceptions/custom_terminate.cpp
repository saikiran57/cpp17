/**
 * @file custom_terminate.cpp
 * @author Saikiran Nadipilli (saikirannadipilli@gmail.com)
 * @brief
 * @version 0.1
 * @date 2026-02-05
 *
 *  @ref: https://www.studyplan.dev/pro-cpp/terminate-noexcept
 *
 * @copyright Copyright (c) 2026
 *
 */

#include <chrono>
#include <exception>
#include <fstream>
#include <iostream>
#include <thread>

void customTerminate()
{
    std::ofstream crash("crash.log", std::ios::app);

    crash << "========= CRASH REPORT =========\n";
    crash << "Time: " << std::time(nullptr) << "\n";

    if (auto eptr = std::current_exception())
    {
        try
        {
            std::rethrow_exception(eptr);
        }
        catch (const std::exception& e)
        {
            crash << "Unhandled std::exception: " << e.what() << "\n";
        }
        catch (...)
        {
            crash << "Unhandled unknown exception.\n";
        }
    }

#if __cpp_lib_stacktrace
    crash << "Stacktrace:\n" << std::stacktrace::current() << "\n";
#endif

    crash << "Flushing logs and terminating...\n";
    crash.flush();

    std::this_thread::sleep_for(std::chrono::milliseconds(100));  // let logs flush
    std::abort();
}

int main()
{
    std::set_terminate(customTerminate);

    throw std::runtime_error("memory corruption detected");
}