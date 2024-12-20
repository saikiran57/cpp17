// C++ program to calculate the Prime
// Numbers upto 10000000 using Sieve
// of Eratosthenes with NO optimization

#include "execution_timer.hpp"
#include <chrono>
#include <cmath>
#include <iostream>
#include <vector>

#define N 10000005
using namespace std;

// Boolean array for Prime Number
vector<bool> prime(N, true);

// Sieve implemented to find Prime
// Number
void sieveOfEratosthenes()
{
    for (int i = 2; i <= sqrt(N); ++i)
    {
        if (prime[i])
        {
            for (int j = i * i; j <= N; j += i)
            {
                prime[j] = false;
            }
        }
    }
}

// Driver Code
int main()
{
    // Initialise clock to calculate
    // time required to execute without
    // optimization
    // std::chrono::system_clock start, end;

    // Start clock
    auto start = std::chrono::steady_clock::now();

    // ExecutionTimer et;
    //  Function call to find Prime Numbers
    sieveOfEratosthenes();

    // End clock
    auto end = std::chrono::steady_clock::now();

    // Calculate the time difference
    auto time_taken = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();

    // Print the Calculated execution time
    cout << "Execution time: " << time_taken << " milli secs\n";

    return 0;
}
