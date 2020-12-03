#include <iostream>
#include <fstream>
#include <string>
#include <vector>
int main(int arg, char* argv[]) 
{
    std::ifstream file { std::string(argv[1]) };

    int w;
    std::string str;
    std::vector<std::vector<int>> map;
    while (getline(file, str))
    {   
        w = str.size();
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
        std::cout << count << "\n";
        prod *= count;
    }
    std::cout << prod << "\n";
}