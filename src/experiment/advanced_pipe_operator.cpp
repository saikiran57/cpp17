#include <concepts>
#include <iostream>
#include <string>
#include <utility>
#include <vector>

// 1. Basic function pointer version with perfect forwarding
// template<typename T>
// std::string operator|(T&& data, std::string(*func)(std::string))
// {
//     return func(std::forward<T>(data));
// }

// 2. Generic callable version with perfect forwarding
template <typename T, typename F>
requires std::is_invocable_r_v<std::string, F, T>
constexpr std::string operator|(T&& data, F&& func)
{
    return std::forward<F>(func)(std::forward<T>(data));
}

// Generic Return Type
// template <typename T, typename Function>
// requires (std::invocable<Function, T>)
// constexpr auto operator | (T &&t, Function &&f)
//     -> typename std::invoke_result_t<Function, T>
// {
//     return std::invoke(std::forward<Function>(f), std::forward<T>(t));
// }

// Example functions showing different parameter types
class StringProcessor
{
public:
    // Member function
    std::string process(std::string data) const
    {
        return "Processed: " + data;
    }

    // Operator overload
    std::string operator()(std::string data) const
    {
        return "Functor: " + data;
    }
};

// Free functions
std::string add_header(std::string data)
{
    return "Header: " + data;
}

std::string add_footer(const std::string& data)
{
    return data + " :Footer";
}

std::string transform_rvalue(std::string&& data)
{
    data = "RVALUE: " + data;
    return std::move(data);
}

int main()
{
    std::cout << "=== Perfect Forwarding Demo ===\n";

    std::string name = "Sai";

    // Case 1: Starting with lvalue - copies
    std::cout << "\n1. Lvalue chain (copies):\n";
    std::string result1 = name | add_header  // gets lvalue, copies
                          | add_footer;      // gets lvalue, copies
    std::cout << "Result: " << result1 << std::endl;
    std::cout << "Original: " << name << " (still intact)\n";

    // Case 2: Starting with rvalue - moves
    std::cout << "\n2. Rvalue chain (moves):\n";
    std::string result2 = std::string("Temp") | add_header  // gets rvalue, moves
                          | transform_rvalue                // gets rvalue, moves
                          | add_footer;                     // gets rvalue, moves
    std::cout << "Result: " << result2 << std::endl;

    // Case 3: Mixed - demonstrates perfect forwarding preserving value category
    std::cout << "\n3. Mixed chain:\n";
    std::string another = "Test";
    std::string result3 = std::move(another)  // Convert to rvalue
                          | add_header        // gets rvalue, moves
                          | add_footer;       // gets rvalue (from add_header), moves
    std::cout << "Result: " << result3 << std::endl;
    std::cout << "Original after move: '" << another << "' (empty)\n";

    // Case 4: With functors and lambdas
    std::cout << "\n4. Functors and lambdas:\n";
    StringProcessor processor;
    auto lambda = [](std::string s) {
        return "Lambda: " + s;
    };

    std::string result4 = std::string("Object") | processor  // member function object
                          | lambda                           // lambda
                          | add_footer;                      // free function
    std::cout << "Result: " << result4 << std::endl;

    // Case 5: Complex transformations
    std::cout << "\n5. Complex transformation:\n";
    auto pipeline = [](std::string s) {
        s = "Start: " + s;
        for (char& c : s)
            c = std::toupper(c);
        return s;
    };

    std::string data = "hello";
    std::string result5 = std::move(data) | pipeline | [](std::string s) {
        return s + "!!!";
    } | add_footer;
    std::cout << "Result: " << result5 << std::endl;

    return 0;
}