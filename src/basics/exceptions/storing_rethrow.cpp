/**
 * @file storing_rethrow.cpp
 * @author Saikiran Nadipilli (saikirannadipilli@gmail.com)
 * @brief
 * @version 0.1
 * @date 2025-06-11
 *
 * @copyright Copyright (c) 2025
 *
 */

#include <iostream>
#include <stdexcept>
#include <string>

/**
 * ref: https://www.studyplan.dev/pro-cpp/rethrowing-exceptions
 */

/**
 * Storing and rethrowing exceptions
 *
 */

class AuthenticationError : public std::exception
{
public:
    AuthenticationError() = default;

    const char* what() const noexcept override
    {
        return "Invalid username";
    }
};

// login
void login(const std::string& username, const std::string& password)
{
    throw AuthenticationError();
}

// Understanding std::exception_ptr

void HandleException(std::runtime_error& e)
{
    std::cout << "Handled std::runtime_error";
}

void PassException()
{
    try
    {
        throw std::logic_error{"Error"};
    }
    catch (std::runtime_error& e)
    {
        HandleException(e);
    }
}

class SomeError : public std::exception
{
};

void NewWayHandleException(const std::exception_ptr ex)
{
    if (ex)
    {
        try
        {
            std::cout << "exception is there\n";
            std::rethrow_exception(ex);
        }
        catch (const std::runtime_error& e)
        {
            std::cerr << e.what() << '\n';
        }
        catch (const SomeError& e)
        {
            std::cerr << e.what() << "\n";
        }
        catch (...)
        {
            // again rethrow exception
            std::rethrow_exception(ex);
        }
    }
    else
    {
        std::cout << "no exception caught\n";
    }
}

int main()
{
    try
    {
        login("test", "password");
    }
    catch (const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }

    // PassException();

    try
    {
        throw std::logic_error("Not a valid number");
    }
    catch (...)
    {
        try
        {
            NewWayHandleException(std::current_exception());
        }
        catch (...)
        {
            std::cerr << "final excption handling\n";
        }
    }

    return 0;
}