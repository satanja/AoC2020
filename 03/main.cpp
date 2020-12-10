#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include "stefan.h"

void aoc03(const char *arr, int len, unsigned char **out)
{
    std::string in(arr, arr + len);
    std::istringstream file(in);
    std::ostringstream cout((char*) *out);
    int w;
    std::string str;
    std::vector<std::vector<int>> map;
    while (getline(file, str))
    {   
        w = (int) str.size();
        std::vector<int> scan(str.size(), 0);
        int j = 0;
        for (auto const& c : str)
        {
            if (c == '#')
            {
                scan[j] = 1;
            }
            j++;
        }
        map.push_back(scan);
    }

    std::vector<std::pair<int, int>> slopes;
    slopes.push_back(std::make_pair(1,1));
    slopes.push_back(std::make_pair(3,1));
    slopes.push_back(std::make_pair(5,1));
    slopes.push_back(std::make_pair(7,1));
    slopes.push_back(std::make_pair(1,2));
    

    long long prod = 1;
    for (const auto& p : slopes)
    {
        int dx = p.first;
        int dy = p.second;
        int x = dx;
        int y = dy;
        
        long long count = 0;
        while (y < map.size())
        {
            count += map[y][x % w];
            x += dx;
            y += dy;
        }
        prod *= count;
    }
    cout << prod << "\n";
}