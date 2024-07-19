/**
 * @file random_number.cpp
 * @author Saikiran Nadipilli
 * @brief
 * @version 0.1
 * @date 2024-05-18
 *
 * @copyright Copyright (c) 2024
 *
 */

#include <iostream>
#include <random>

int randomNumberInt(int low = 0, int high = 100)
{
    // Create random device to seed the random number engine
    std::random_device rd;

    // Use mergen twister engine
    std::mt19937 gen(rd());

    // Define uniform integer distribution
    std::uniform_int_distribution<> dist(low, high);

    // generate a random number
    int randomNumber = dist(gen);

    return randomNumber;
}

double randomNumberReal(double low = 0.0, double high = 1.0)
{
    // Create random device to seed the random number engine
    std::random_device rd;

    // Use mergen twister engine
    std::mt19937 gen(rd());

    // Define uniform real distribution
    std::uniform_real_distribution<> dist(low, high);

    // generate a random number
    double randomNumber = dist(gen);

    return randomNumber;
}

int main()
{
    std::cout << "random number integer:" << randomNumberInt() << "\n";
    std::cout << "random number real:" << randomNumberReal() << "\n";
}
