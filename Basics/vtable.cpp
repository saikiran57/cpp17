#include <cstdlib>
#include <iostream>

struct Pokemon
{
    Pokemon()
    {
        std::cout << "Pokemon::Pokemon\n";
    };
    virtual ~Pokemon()
    {
        std::cout << "Pokemon::~Pokemon\n";
    };
    /* These methods must be 'pure' virtual and set to 0.
     * This informs the compiler that the method *must* be
     * overwritten by a child class. Otherwise, the compiler
     * assumes that there is an implementation somewhere.
     * Taken literally, we're defining a NULL implementation.
     */
    virtual void cry(void) = 0;
    virtual void attack(void) = 0;
    virtual void flee(void) = 0;
};

struct Caterpie : Pokemon
{
    Caterpie()
    {
        std::cout << "Caterpie::Caterpie\n";
    };
    virtual ~Caterpie()
    {
        std::cout << "Caterpie::~Caterpie\n";
    };
    virtual void cry(void) override
    {
        std::cout << "Caterpie says 'Caterpie!'\n";
    };
    virtual void attack(void) override
    {
        std::cout << "Caterpie used string shot!\n";
    };
    virtual void flee(void) override
    {
        std::cout << "Caterpie fled!\n";
    };
};

struct Weedle : Pokemon
{
    Weedle()
    {
        std::cout << "Weedle::Weedle\n";
    };
    virtual ~Weedle()
    {
        std::cout << "Weedle::~Weedle\n";
    };
    virtual void cry(void) override
    {
        std::cout << "Weedle says 'Weedle!'\n";
    };
    virtual void attack(void) override
    {
        std::cout << "Weedle used poison string!\n";
    };
    virtual void flee(void) override
    {
        std::cout << "Weedle fled!\n";
    };
};

int main(int argc, const char* argv[])
{
    /* Seed the random number. */
    srand((unsigned int)time(NULL));

    /* Create a generic Pokemon. */
    Pokemon* pokemon;

    /* Flip a coin to see which version we're playing. */
    if (rand() % 2)
    {
        std::cout << "You're playing Pokemon Red!\n";
        pokemon = new Weedle();
    }
    else
    {
        std::cout << "You're playing Pokemon Yellow!\n";
        pokemon = new Caterpie;
    }
    /* Make the Pokemon do some tricks. */
    pokemon->cry();
    pokemon->attack();
    pokemon->flee();

    return EXIT_SUCCESS;
}