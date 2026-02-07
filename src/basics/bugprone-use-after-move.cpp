#include <algorithm>
#include <cstddef>
#include <iostream>
#include <string>
#include <vector>

template <class T, class P>
static void remove_if(std::vector<T>& v, P&& predicate)
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
    std::string m_name;
    int m_age{};
};

int main()
{
    std::vector<Person> persons = {Person{.m_name = "John", .m_age = 30}, Person{.m_name = "Mary", .m_age = 2},
                                   Person{.m_name = "von", .m_age = 20}, Person{.m_name = "hus", .m_age = 250}};

    // auto end = std::remove_if(persons.begin(), persons.end(), [](const Person& p) { return p.age < 20; });
    // persons.erase(end, persons.end());

    remove_if(persons, [](const Person& p) {
        return p.m_age < 20;
    });

    for (const auto& p : persons)
    {
        std::cout << p.m_name << " " << p.m_age << "\n";
    }
}
