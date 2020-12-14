#include <bitset>
#include <unordered_map>
#include <array>
#include <vector>
#include <fstream>
#include <string>
#include <iostream>

#if WIN32
    #define SHIFT(k) 1i64 << k
#else 
    #define SHIFT(k) 1 << k
#endif

void bruteforce(
    std::unordered_map<int64_t, int64_t>& memory,
    const std::array<char, 36>& mask,
    int64_t addr,
    int64_t val,
    int index,
    int max
)
{
    if (index == max)
    {
        memory.insert_or_assign(addr, val);
    }
    else
    {
        int64_t addr1 = addr | SHIFT(mask[index]);
        int64_t addr2 = addr & ~(SHIFT(mask[index]));
        bruteforce(memory, mask, addr1, val, index + 1, max);
        bruteforce(memory, mask, addr2, val, index + 1, max);
    }
}

int main(int arg, char* argv[])
{
    std::ifstream file { std::string(argv[1]) };
    std::string line;

    std::unordered_map<int, int64_t> memory;
    std::unordered_map<int64_t, int64_t> memory2;
    std::array<char, 36> mask;
    std::array<char, 36> mask2;
    int max = 0;
    while (getline(file, line))
    {
        if (line.at(1) == 'e')
        {
            // mem
            int addr = 0;
            int i;
            for (i = 4; i < line.size(); i++)
            {
                if (line.at(i) == ']') break;
                addr *= 10;
                addr += line.at(i) - '0';
            }
            int64_t val = std::stoll(line.substr(i + 4));
            int64_t addr2 = addr;
            // part 2
            for (int j = 0; j < mask.size(); j++)
            {
                char c = mask[j];
                if (c == 'X' - '0') continue;
                if (c)
                {
                    addr2 |= SHIFT(j);
                }
            }
            bruteforce(memory2, mask2, addr2, val, 0, max);

            // part 1
            for (int j = 0; j < mask.size(); j++)
            {
                char c = mask[j];
                if (c == 'X' - '0') continue;
                if (c)
                {
                    val |= SHIFT(j);
                }
                else 
                {
                    val &= ~(SHIFT(j));
                }
            }

            memory.insert_or_assign(addr, val);
        }
        else 
        {
            int j = 35;
            max = 0;
            for (int i = 7; i < line.size(); i++)
            {
                mask[j] = line.at(i) - '0';
                if (line.at(i) == 'X')
                {
                    mask2[max++] = j;
                }
                j--;
            }

        }
    }

    int64_t p1 = 0;
    for (auto [k , v] : memory)
    {
        p1 += v;
    }

    int64_t p2 = 0;
    for (auto [k , v] : memory2)
    {
        p2 += v;
    }

    std::cout << p1 << "\n";
    std::cout << p2 << "\n";
}