#include <iostream>
#include <vector>

/**
 * https://en.cppreference.com/w/cpp/iterator
 * https://www.geeksforgeeks.org/iterators-c-stl/?ref=ml_lbp
 * 
 * Iterators are used to point at the memory address of stl containers
 * Iterators Operations c++17
 * 
 * Advance
 * 
 * distance
 * 
 * next
 * 
 * prev
 * 
*/
int main()
{
    std::vector<int> vec{1,2,3,4,5,6,7,8,9};
    auto vecBegin = vec.begin();
    auto vecEnd = vec.end();

    // advance increment iterators by n elements
    std::advance(vecBegin, 2);
    std::cout << "vecBegin+2:" << *vecBegin << "\n";

    // advance decrement by -2
    std::advance(vecEnd, -2);
    std::cout << "vec decrement:" << *vecEnd << "\n";

    // std::next(it,n) returns nth successor(or -nth predecessor if is n is negative) of iterator it
    auto it = vec.begin();
    auto nx = std::next(it, 2);
    std::cout << "nx: " << *nx << "\n";

    it = vec.end();
    nx = std::next(it, 2);
    if (nx != it)
    {
        std::cout << "nx: " << *nx << "\n";
    }

    return 0;
}