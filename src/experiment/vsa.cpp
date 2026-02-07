#include <array>
#include <iostream>
#include <map>
#include <string>
#include <vector>

std::map<int, std::string> vsa;

constexpr int MAX_SIZE = 235;

void send(int key)
{
    auto encoded = vsa[key];
    std::cout << "vsa: " << key << " encoded: " << encoded << "\n";
    vsa[key] = "";
}

void sender(int key, const std::string& field)
{
    auto len = field.length();

    if (len > MAX_SIZE) return;

    auto it = vsa.find(key);

    if (it != vsa.end())
    {
        std::string encodedString = it->second;
        if (encodedString.size() + len <= MAX_SIZE)
        {
            encodedString += field;
            vsa[key] = encodedString;
        }

        if (encodedString.size() == MAX_SIZE || encodedString.size() + len > MAX_SIZE)
        {
            // send
            send(key);

            if (encodedString.size() + len > MAX_SIZE)
            {
                encodedString.clear();
                encodedString += field;
                vsa[key] = encodedString;
            }
        }
    }
}

int main(int argc, char const* argv[])
{
    std::array<int, 4> keys{182, 183, 184, 185};

    vsa[182] = "";
    vsa[183] = "";
    vsa[184] = "";
    vsa[185] = "";

    int i = 0;
    std::string field = "abcdefghijklmnopqrstuvwxyz0";
    while (i < 400)
    {
        auto nf = std::to_string(i) + field;
        int index = i % 4;
        sender(keys[index], nf);
        ++i;
    }

    return 0;
}
