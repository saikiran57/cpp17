#include <chrono>
#include <cstddef>
#include <iostream>
#include <vector>

static constexpr size_t NUMBER_OF_ELEMENTS = 2'000'000'000;  // 2 billion

void test_constructor()
{
    std::cout << "\n=== Test 1: Constructor with size ===\n";
    auto begin = std::chrono::system_clock::now();

    std::vector<int> vec(NUMBER_OF_ELEMENTS);  // Allocates + initializes ALL

    std::cout << "capacity: " << vec.capacity() << " size: " << vec.size() << "\n";
    vec[1024] = 47;
    int j = vec[1024];
    vec.push_back(23);  // Will cause reallocation!

    auto end = std::chrono::system_clock::now();
    auto micros = std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count();
    std::cout << "Time: " << micros / 1'000'000.0 << " seconds\n";
}

void test_reserve()
{
    std::cout << "\n=== Test 2: reserve() only ===\n";
    auto begin = std::chrono::system_clock::now();

    std::vector<int> vec;
    vec.reserve(NUMBER_OF_ELEMENTS);  // Allocates but doesn't initialize

    std::cout << "capacity: " << vec.capacity() << " size: " << vec.size() << "\n";

    // Need to add elements before accessing
    for (int i = 0; i < 1025; ++i)
    {
        vec.push_back(i);  // These will be in reserved space - no reallocation
    }

    vec[1024] = 47;
    int j = vec[1024];
    vec.push_back(23);  // Still within reserved space

    std::cout << "capacity: " << vec.capacity() << " size: " << vec.size() << "\n";

    auto end = std::chrono::system_clock::now();
    auto micros = std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count();
    std::cout << "Time: " << micros / 1'000'000.0 << " seconds\n";
}

void test_constructor_no_init()
{
    std::cout << "\n=== Test 3: Constructor without initialization (C++20) ===\n";
    auto begin = std::chrono::system_clock::now();

    // C++20: std::vector<int> vec(NUMBER_OF_ELEMENTS);  // Still initializes!
    // For no initialization, need custom allocator or:
    std::vector<int> vec;
    vec.reserve(NUMBER_OF_ELEMENTS);

    // "Create" elements without initialization (UB if read before write!)
    for (size_t i = 0; i < 1025; ++i)
    {
        vec.emplace_back();  // Still default-initializes! (C++11-17)
    }

    vec[1024] = 47;
    int j = vec[1024];
    vec.push_back(23);

    std::cout << "capacity: " << vec.capacity() << " size: " << vec.size() << "\n";

    auto end = std::chrono::system_clock::now();
    auto micros = std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count();
    std::cout << "Time: " << micros / 1'000'000.0 << " seconds\n";
}

// C++17: Uninitialized memory with std::allocator
void test_uninitialized()
{
    std::cout << "\n=== Test 4: Truly uninitialized (advanced) ===\n";
    auto begin = std::chrono::system_clock::now();

    std::allocator<int> alloc;
    int* ptr = alloc.allocate(NUMBER_OF_ELEMENTS);  // Raw memory, no initialization

    std::cout << "Raw memory allocated: " << NUMBER_OF_ELEMENTS << " ints\n";

    // Construct only what we need
    new (&ptr[1024]) int(47);  // Construct at specific location

    int j = ptr[1024];

    // Must destroy and deallocate
    std::destroy_at(&ptr[1024]);
    alloc.deallocate(ptr, NUMBER_OF_ELEMENTS);

    auto end = std::chrono::system_clock::now();
    auto micros = std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count();
    std::cout << "Time: " << micros / 1'000'000.0 << " seconds\n";
}

int main()
{
    std::cout << "Testing with " << NUMBER_OF_ELEMENTS << " elements ("
              << (NUMBER_OF_ELEMENTS * sizeof(int)) / (1024.0 * 1024 * 1024) << " GB)\n\n";

    try
    {
        // This will likely be VERY slow or crash
        // test_constructor();

        // This should be fast
        test_reserve();

        test_constructor_no_init();

        test_uninitialized();
    }
    catch (const std::exception& e)
    {
        std::cout << "Exception: " << e.what() << "\n";
    }

    return 0;
}