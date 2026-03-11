/**
 * @file pipe_functions.cpp
 * @author Saikiran Nadipilli (saikirannadipilli@gmail.com)
 * @brief
 * @version 0.1
 * @date 2026-02-20
 *
 * @copyright Copyright (c) 2026
 *
 */

// #include <iostream>
// #include <functional>
// #include <string>

// // Generic pipe operator implementation
// template <typename T, typename Function>
// auto operator|(T&& t, Function&& f) -> decltype(f(std::forward<T>(t))) {
//     return std::forward<Function>(f)(std::forward<T>(t));
// }

// // Example functions
// std::string addHeader(std::string s) { return "Header: " + s; }
// std::string addFooter(std::string s) { return s + " :Footer"; }

// int main() {
//     std::string data = "Hello World";

//     // Using the pipe operator
//     auto result = data | addHeader | addFooter;

//     std::cout << result << std::endl; // Output: Header: Hello World :Footer
//     return 0;
// }

#include <iostream>

using Function = std::string (*)(std::string);

std::string operator|(std::string data, Function func)
{
    return func(std::move(data));
}

// Example functions
std::string add_header(std::string data)
{
    return "Hello " + data;
}
std::string add_footer(std::string data)
{
    return data + "!";
}

int main()
{
    // Works with lambdas too
    auto repeat = [](std::string s) {
        return s + " " + s;
    };
    auto exclaim = [](std::string s) {
        return s + "!!!";
    };

    auto wrong = [](int s) {
        return std::to_string(s);
    };

    std::string result = std::string("Sai") | add_header | repeat | exclaim | add_footer;

    std::cout << result << std::endl;  // Hello Sai Hello Sai!!!

    return 0;
}