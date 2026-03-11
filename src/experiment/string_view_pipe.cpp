#include <algorithm>
#include <concepts>
#include <iostream>
#include <ranges>
#include <string>
#include <string_view>

namespace sv_pipe
{

// Concept for string-like types
template <typename T>
concept StringLike = std::is_convertible_v<T, std::string_view>;

// Concept for string view transformers (string -> string)
template <typename F>
concept StringTransformer = std::is_invocable_r_v<std::string, F, std::string_view>;

// Concept for general transformers (string -> anything)
template <typename F, typename R>
concept TransformerTo = std::is_invocable_r_v<R, F, std::string_view>;

// Lazy transform wrapper for function composition
template <typename F>
class LazyTransform
{
    F func;

public:
    constexpr explicit LazyTransform(F f) : func(std::move(f)) {}

    // Apply to a string
    template <StringLike T>
    constexpr auto operator()(T&& input) const
    {
        return func(std::string_view{std::forward<T>(input)});
    }

    // Function composition operator - handles both lvalue and rvalue
    template <typename G>
    constexpr friend auto operator|(const LazyTransform<F>& lhs, const LazyTransform<G>& rhs)
    {
        return LazyTransform{[lhs_func = lhs.func, rhs_func = rhs.func](std::string_view sv) -> std::string {
            return rhs_func(lhs_func(sv));
        }};
    }

    template <typename G>
    constexpr friend auto operator|(LazyTransform<F>&& lhs, const LazyTransform<G>& rhs)
    {
        return LazyTransform{[lhs_func = std::move(lhs.func), rhs_func = rhs.func](std::string_view sv) -> std::string {
            return rhs_func(lhs_func(sv));
        }};
    }

    template <typename G>
    constexpr friend auto operator|(const LazyTransform<F>& lhs, LazyTransform<G>&& rhs)
    {
        return LazyTransform{[lhs_func = lhs.func, rhs_func = std::move(rhs.func)](std::string_view sv) -> std::string {
            return rhs_func(lhs_func(sv));
        }};
    }

    template <typename G>
    constexpr friend auto operator|(LazyTransform<F>&& lhs, LazyTransform<G>&& rhs)
    {
        return LazyTransform{
            [lhs_func = std::move(lhs.func), rhs_func = std::move(rhs.func)](std::string_view sv) -> std::string {
                return rhs_func(lhs_func(sv));
            }};
    }
};

// Pipe operator for string -> LazyTransform (executes the transform)
template <StringLike T, typename F>
constexpr auto operator|(T&& input, const LazyTransform<F>& transform)
{
    return transform(std::forward<T>(input));
}

// Pipe operator for string -> function (direct execution) - returns string
template <StringLike T, StringTransformer F>
constexpr std::string operator|(T&& input, F&& func)
{
    return func(std::string_view{std::forward<T>(input)});
}

// Pipe operator for string -> function with different return type
template <StringLike T, typename F, typename R>
requires TransformerTo<F, R> && (!StringTransformer<F>)
constexpr R operator|(T&& input, F&& func)
{
    return func(std::string_view{std::forward<T>(input)});
}

// Helper to create lazy transforms
template <typename F>
constexpr auto lazy(F&& f)
{
    return LazyTransform<std::decay_t<F>>{std::forward<F>(f)};
}

// Common transforms (as lazy by default)
inline constexpr auto header = lazy([](std::string_view sv) {
    return std::string("Header: ") + std::string(sv);
});

inline constexpr auto footer = lazy([](std::string_view sv) {
    return std::string(sv) + " :Footer";
});

inline constexpr auto upper = lazy([](std::string_view sv) {
    std::string result{sv};
    std::ranges::transform(result, result.begin(), [](unsigned char c) {
        return std::toupper(c);
    });
    return result;
});

inline constexpr auto lower = lazy([](std::string_view sv) {
    std::string result{sv};
    std::ranges::transform(result, result.begin(), [](unsigned char c) {
        return std::tolower(c);
    });
    return result;
});

inline constexpr auto reverse = lazy([](std::string_view sv) {
    std::string result{sv};
    std::reverse(result.begin(), result.end());
    return result;
});

inline constexpr auto trim = lazy([](std::string_view sv) {
    auto not_space = [](unsigned char c) {
        return !std::isspace(c);
    };
    auto begin = std::ranges::find_if(sv, not_space);
    auto end = std::ranges::find_if(sv | std::views::reverse, not_space).base();
    return std::string(begin, end);
});

inline constexpr auto repeat = lazy([](std::string_view sv) {
    return std::string(sv) + " " + std::string(sv);
});

inline constexpr auto exclaim = lazy([](std::string_view sv) {
    return std::string(sv) + "!!!";
});

// Word count (returns size_t)
inline constexpr auto word_count = [](std::string_view sv) -> size_t {
    auto words = sv | std::views::split(' ') | std::views::filter([](auto w) {
                     return !w.empty();
                 });
    return std::ranges::distance(words);
};

// Length (returns size_t)
inline constexpr auto length = [](std::string_view sv) -> size_t {
    return sv.size();
};

// Check if palindrome (returns bool)
inline constexpr auto is_palindrome = [](std::string_view sv) -> bool {
    auto begin = sv.begin();
    auto end = sv.end() - 1;
    while (begin < end)
    {
        if (*begin != *end) return false;
        ++begin;
        --end;
    }
    return true;
};

// First character (returns optional<char>)
inline constexpr auto first_char = [](std::string_view sv) -> std::optional<char> {
    if (sv.empty()) return std::nullopt;
    return sv[0];
};
}  // namespace sv_pipe

int main()
{
    using namespace sv_pipe;

    std::cout << "=== Fixed string_view Pipeline ===\n\n";

    // 1. Function composition using | (now works!)
    std::cout << "1. Function composition:\n";
    auto pipeline = header | upper | footer;  // Now works!
    std::string result1 = "hello world" | pipeline;
    std::cout << "Pipeline result: " << result1 << "\n\n";

    // 2. Different input with same pipeline
    std::cout << "2. Reusing pipeline:\n";
    std::cout << "With 'test': " << ("test" | pipeline) << "\n";
    std::cout << "With 'C++23': " << ("C++23" | pipeline) << "\n\n";

    // 3. Complex composition
    std::cout << "3. Complex composition:\n";
    auto complex = header | lower | reverse | upper | footer;
    std::cout << "Complex: " << ("Mixed Case Input" | complex) << "\n\n";

    // 4. Non-string results
    std::cout << "4. Non-string results:\n";
    std::string text = "one two three four";
    size_t words = text | word_count;
    size_t len = text | length;
    bool pal = "racecar" | is_palindrome;
    auto first = text | first_char;

    std::cout << "Text: \"" << text << "\"\n";
    std::cout << "Word count: " << words << "\n";
    std::cout << "Length: " << len << "\n";
    std::cout << "Is 'racecar' palindrome? " << std::boolalpha << pal << "\n";
    if (first)
    {
        std::cout << "First character: " << *first << "\n\n";
    }

    // 5. Mixed direct and composed
    std::cout << "5. Mixed operations:\n";
    auto result2 = "  Hello World  " | trim  // direct function call
                   | header                  // composed with header
                   | upper                   // composed with upper
                   | footer;                 // composed with footer
    std::cout << "Trimmed and transformed: " << result2 << "\n\n";

    // 6. Performance demonstration
    std::cout << "6. Performance demonstration:\n";
    const std::string long_text = "This is a very long string that demonstrates the efficiency of string_view";

    // Using composition (minimal copies)
    auto composed = upper | reverse | lower;
    std::string composed_result = long_text | composed;
    std::cout << "Composed result length: " << composed_result.length() << "\n";

    // Direct chaining (still efficient due to string_view)
    std::string direct_result = long_text | [](std::string_view sv) {
        return std::string("START: ") + std::string(sv);
    } | [](std::string_view sv) {
        std::string result{sv};
        std::ranges::transform(result, result.begin(), [](unsigned char c) {
            return std::toupper(c);
        });
        return result;
    } | [](std::string_view sv) {
        return std::string(sv) + " :END";
    };

    std::cout << "Direct result length: " << direct_result.length() << "\n\n";

    // 7. Custom transforms
    std::cout << "7. Custom transforms:\n";
    auto custom = repeat | exclaim | upper;
    std::cout << "Custom: " << ("hello" | custom) << "\n\n";

    // 8. Chaining multiple compositions
    std::cout << "8. Multiple compositions:\n";
    auto p1 = header | upper;
    auto p2 = reverse | footer;
    auto combined = p1 | p2;  // Compose two pipelines
    std::cout << "Combined: " << ("test" | combined) << "\n";

    return 0;
}