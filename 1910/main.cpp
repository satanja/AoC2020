#include <fstream>
#include <string>
#include <set>
#include <utility>
#include <vector>
#include <numeric>
#include <iostream>

bool is_visible(
    const std::pair<int, int>& a,
    const std::pair<int, int>& b,
    std::set<std::pair<int,int>>& slopes)
{
    int dx = b.first - a.first;
    int dy = b.second - a.second;
    
    int g = std::gcd(dx, dy);
    std::pair<int,int> slope(dx / g, dy / g);
    
    if (!slopes.contains(slope))
    {
        slopes.insert(slope);
        return true;
    }
    return false;
}

int main(int arg, char* argv[])
{
    std::ifstream file { std::string(argv[1]) };
    std::string line;

    std::vector<std::pair<int,int>> asteroids;
    int y = 0;
    while (getline(file, line))
    {
        for (int x = 0; x < line.size(); x++)
        {
            if (line.at(x) == '#')
            {
                asteroids.emplace_back(x, y);
            }
        }
        y++;
    }

    int max_visible = -1;
    for (int i = 0; i < asteroids.size(); i++)
    {
        int visible = 0;
        std::set<std::pair<int,int>> slopes;
        for (int j = 0; j < asteroids.size(); j++)
        {
            if (i == j) continue;
            bool v = is_visible(asteroids[i], asteroids[j], slopes);
            visible += v;
        }
        
        if (visible > max_visible)
        {
            max_visible = visible;
        }
    }

    std::cout << max_visible << "\n";
}