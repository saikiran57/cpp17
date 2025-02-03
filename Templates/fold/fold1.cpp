// https://godbolt.org/z/hex1Yzdj1

#include <cstdarg>
#include <iostream>
#include <memory>

template <typename TupleT>
void printTupleApply(const TupleT& tp)
{
    std::cout << "(";
    if constexpr (std::tuple_size_v<TupleT> >= 0u)
        std::apply(
            [](const auto& a0, const auto&... a1) {
                std::cout << a0;
                ((std::cout << ", " << a1), ...);
            },
            tp);
    std::cout << ")";
}

int main()
{
    std::tuple tp{10, 20, 3.14, 42, "hello"};
    printTupleApply(tp);
}
