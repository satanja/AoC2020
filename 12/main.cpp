#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <utility>
#include <vector>
#include <chrono>
#include <array>

inline int map_char(
    const std::array<char, 7>& index,
    const std::array<char, 7>& map,
    const char c)
{
    auto ptr = std::lower_bound(index.begin(), index.end(), c); // binary search jonges!
    int i = ptr - index.begin();
    return map[i];
}

inline int stoi(std::string s, int offset)
{
    int k = 0;
    for (int i = offset; i < s.size(); ++i)
    {
        k *= 10;
        k += s.at(i) - '0';
    }
    return k;
}

int main(int arg, char *argv[])
{
    std::ifstream file{std::string(argv[1])};
    auto begin = std::chrono::high_resolution_clock::now();

    std::pair<int, int> directions[] = {
        {1, 0},  // E
        {0, -1}, // S
        {-1, 0}, // W
        {0, 1},  // N
    };
    int facing = 0;
    int x = 0;
    int y = 0;

    std::string l;
    std::vector<std::pair<char, int>> instructions;
    std::array<char, 7> index { 'E', 'F', 'L', 'N', 'R', 'S', 'W' };
    std::array<char, 7> map { 0, 'F', 'L', 3, 'R', 1, 2 };
    while (getline(file, l))
    {
        instructions.emplace_back(map_char(index, map, l.at(0)), stoi(l, 1));
    }

    for (const std::pair<char, int>& p : instructions)
    {
        char c = p.first;
        int d = p.second;
        if (c == 'F')
        {
            x += d * directions[facing].first;
            y += d * directions[facing].second;
        }
        else if (c == 'L')
        {
            facing = (facing - d / 90);
            if (facing < 0)
            {
                facing += 4;
            }
        }
        else if (c == 'R')
        {
            facing = (facing + d / 90);
            if (facing >= 4)
            {
                facing -= 4;
            }
        }
        else
        {
            x += d * directions[c].first;
            y += d * directions[c].second;
        }
    }

    int wx = 10;
    int wy = 1;
    int x2 = 0;
    int y2 = 0;
    std::pair<int, int> rotations[] = {
        {0, 1},  // -270
        {-1, 0}, // -180
        {0, -1}, // -90
        {0, 0},  // 0 dummy
        {0, 1},  // 90
        {-1, 0}, // 180
        {0, -1}  // 270
    };

    for (const std::pair<char, int>& p : instructions)
    {
        char c = p.first;
        int d = p.second;
        if (c == 'F')
        {
            x2 += d * wx;
            y2 += d * wy;
        } 
        else if (c == 'R')
        {
            d *= -1;
            int cos = rotations[d / 90 + 3].first;
            int sin = rotations[d / 90 + 3].second;
            int wxt = wx;
            int wyt = wy;
            wx = wxt * cos - wyt * sin;
            wy = wxt * sin + wyt * cos;
        }
        else if (c == 'L')
        {
            int cos = rotations[d / 90 + 3].first;
            int sin = rotations[d / 90 + 3].second;
            int wxt = wx;
            int wyt = wy;
            wx = wxt * cos - wyt * sin;
            wy = wxt * sin + wyt * cos;
        } 
        else 
        {
            wx += d * directions[c].first;
            wy += d * directions[c].second;
        }
    }

    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration<double, std::micro>(end - begin);
    std::cout << std::abs(x) + std::abs(y) << "\n";
    std::cout << std::abs(x2) + std::abs(y2) << "\n";
    std::cout << duration.count() << "us\n";

    return 0;
}