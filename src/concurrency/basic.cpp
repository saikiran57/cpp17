#include <iostream>
#include <thread>

using namespace std;

void worker()
{
    std::cout << "I am a worker\n";
    this_thread::sleep_for(std::chrono::seconds(10));
}

int main()
{
    cout << "Hello World!" << endl;

    std::thread t(worker);

    std::cout << "Im in main thread and sleeping for 5s\n";
    this_thread::sleep_for(std::chrono::seconds(5));
    t.join();

    return 0;
}
