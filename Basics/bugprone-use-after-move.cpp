#include <algorithm>
#include <iostream>
#include <vector>

template <class T, class P>
void remove_if(std::vector<T>& v, P&& predicate)
{
    size_t new_size = 0;
    for (auto&& x : v)
    {
        if (!predicate(x))
        {
            v[new_size] = std::move(x);  // self-move-assignment!
            ++new_size;
        }
    }
    v.resize(new_size);
}

struct Person
{
    std::string name;
    int age;
};

int main()
{
    std::vector<Person> persons = {Person{"John", 30}, Person{"Mary", 2}, Person{"von", 20}, Person{"hus", 250}};

    // auto end = std::remove_if(persons.begin(), persons.end(), [](const Person& p) { return p.age < 20; });
    // persons.erase(end, persons.end());

    remove_if(persons, [](const Person& p) {
        return p.age < 20;
    });

    for (const auto& p : persons)
    {
        std::cout << p.name << " " << p.age << "\n";
    }
}
