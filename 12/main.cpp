#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <utility>
#include <vector>

int main(int arg, char *argv[])
{
    std::ifstream file{std::string(argv[1])};

    std::pair<int, int> directions[] = {
        {1, 0},  // E
        {0, -1}, // S
        {-1, 0}, // W
        {0, 1},  // N
    };
    int facing = 0;
    int64_t x = 0;
    int64_t y = 0;

    std::string l;
    std::vector<std::string> instructions;
    while (getline(file, l))
    {
        instructions.push_back(l);
    }

    for (std::string &line : instructions)
    {
        int d = std::stoi(line.substr(1));
        if (line.at(0) == 'F')
        {
            x += d * directions[facing].first;
            y += d * directions[facing].second;
        }
        else if (line.at(0) == 'N')
        {
            x += d * directions[3].first;
            y += d * directions[3].second;
        }
        else if (line.at(0) == 'S')
        {
            x += d * directions[1].first;
            y += d * directions[1].second;
        }
        else if (line.at(0) == 'E')
        {
            x += d * directions[0].first;
            y += d * directions[0].second;
        }
        else if (line.at(0) == 'W')
        {
            x += d * directions[2].first;
            y += d * directions[2].second;
        }
        else if (line.at(0) == 'L')
        {
            facing = (facing - d / 90);
            if (facing < 0)
            {
                facing += 4;
            }
        }
        else if (line.at(0) == 'R')
        {
            facing = (facing + d / 90);
            if (facing >= 4)
            {
                facing -= 4;
            }
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

    for (std::string &line : instructions)
    {
        int d = std::stoi(line.substr(1));
        if (line.at(0) == 'R')
        {
            d *= -1;
            int cos = rotations[d / 90 + 3].first;
            int sin = rotations[d / 90 + 3].second;
            int wxt = wx;
            int wyt = wy;
            wx = wxt * cos - wyt * sin;
            wy = wxt * sin + wyt * cos;
        }
        else if (line.at(0) == 'L')
        {
            int cos = rotations[d / 90 + 3].first;
            int sin = rotations[d / 90 + 3].second;
            int wxt = wx;
            int wyt = wy;
            wx = wxt * cos - wyt * sin;
            wy = wxt * sin + wyt * cos;
        }
        else if (line.at(0) == 'F')
        {
            x2 += d * wx;
            y2 += d * wy;
        }
        else if (line.at(0) == 'N')
        {
            wx += d * directions[3].first;
            wy += d * directions[3].second;
        }
        else if (line.at(0) == 'S')
        {
            wx += d * directions[1].first;
            wy += d * directions[1].second;
        }
        else if (line.at(0) == 'E')
        {
            wx += d * directions[0].first;
            wy += d * directions[0].second;
        }
        else if (line.at(0) == 'W')
        {
            wx += d * directions[2].first;
            wy += d * directions[2].second;
        }
    }

    std::cout << std::abs(x) + std::abs(y) << "\n";
    std::cout << std::abs(x2) + std::abs(y2) << "\n";
    return 0;
}