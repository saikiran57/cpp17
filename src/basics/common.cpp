#include <iostream>

class common
{
private:
    /* data
     */

public:
    common(/* args */);
    ~common() noexcept(false);
};

common::common(/* args */) {}

common::~common() noexcept(false)
{
    throw 32;
}

int main()
{
    try
    {
        common c;
    }
    catch (const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
    catch (...)
    {
    }

    return 0;
}
