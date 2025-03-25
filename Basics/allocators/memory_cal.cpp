/**
 * @file memory_cal.cpp
 * @author Saikiran Nadipilli
 * @brief
 * @version 0.1
 * @date 2024-12-13
 *
 * @copyright Copyright (c) 2024
 *
 */

#include <array>
#include <cstddef>
#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>

#include <memory_resource>

static int number_of_new_calls = 0;
static int number_of_delete_calls = 0;
static size_t memory_size = 0;

static void reset_counter()
{
    number_of_new_calls = 0;
    number_of_delete_calls = 0;
    memory_size = 0;
}

void* operator new(size_t size)
{
    void const* ptr = malloc(size);

    if (ptr != nullptr)
    {
        number_of_new_calls++;
        memory_size += size;
        return ptr;
    }

    throw std::bad_alloc{};
}

void operator delete(void* ptr) noexcept
{
    number_of_delete_calls++;
    std::free(ptr);
}

static void new_delete_summary()
{
    std::cout << std::dec << "#new: " << number_of_new_calls << " #delete: " << number_of_delete_calls
              << " #bytes: " << memory_size << std::endl;
    reset_counter();
}

// void showmemory(unsigned char* buffer, std::size_t buffer_size, const char* headline = "")
// {
//     if (headline != "") std::cout << headline << std::endl;
//     std::cout << "&buffer=0x" << std::hex << (unsigned int)(buffer) << " " << std::dec << buffer_size << " bytes"
//               << std::endl;
//     int i = 0;
//     while (i < buffer_size)
//     {
//         int first = i;
//         int last = i + std::min(10, int(buffer_size - first));
//         std::cout << "&=" << std::setw(2) << std::hex << std::size_t(first);
//         std::cout << " asc: ";
//         for (int k = first; k < last; k++)
//         {
//             if ((buffer[k] >= 32) and (buffer[k] <= 127))
//                 std::cout << buffer[k];
//             else
//                 std::cout << ".";
//         }
//         i = i + 10;
//         std::cout << std::endl;
//     }
//     std::cout << std::endl;
// }

static void one_explicit_new_and_delete()
{
    int const* pi = new int;
    delete pi;
}

static void vector_with_implicit_heap_allocations()
{
    std::vector<int> v;
    // v.reserve(10);
    for (int i = 0; i < 10; i++)
    {
        v.push_back(i);
    }
}

static void vector_with_stack_memory(int n)
{                                                 // The only difference are the first three statements:
    std::array<unsigned char, 100'000> memory{};  // local definition
                                                  // use memory as memory for the vector and the strings:
    std::pmr::monotonic_buffer_resource pool{memory.data(), memory.size()};
    std::pmr::vector<std::pmr::string> container{&pool};  // see 7.
    // work with the container
    for (int i = 0; i < n; ++i)
    {
        container.emplace_back("A string with more than 16 chars");
    }
}  // #new: 0 #delete: 0 #bytes: 0

static void vector_with_heap_memory(int n)
{
    std::vector<std::string> container;
    // work with the container
    for (int i = 0; i < n; ++i)
    {
        container.emplace_back("A string with more than 16 chars");
    }
}  // #new: 0 #delete: 0 #bytes: 0

int main()
{
    vector_with_implicit_heap_allocations();
    // vector_with_heap_memory(10);
    // vector_with_stack_memory(10);
    new_delete_summary();
    return 0;
}