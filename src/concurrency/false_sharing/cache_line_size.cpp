#include <iostream>
#ifdef __cpp_lib_hardware_interference_size
#include <new>

constexpr size_t cache_line_size = std::hardware_destructive_interference_size;

int main()
{
    std::cout << "Cache line size: " << cache_line_size << " bytes\n";
}
#else
// Fallback for older C++ versions
int main()
{
    std::cout << "C++17 hardware interference size not available\n";
}
#endif
