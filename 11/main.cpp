#include <fstream>
#include <sstream>
#include <iostream>
#include <string>
#include <utility>

int occupied(int x, int y, const std::array<std::array<char, 100>, 100>& state)
{
    int occ = 0;
    occ += state[y][x - 1] == 2;
    occ += state[y][x + 1] == 2;
    occ += state[y + 1][x + 1] == 2;
    occ += state[y + 1][x - 1] == 2;
    occ += state[y - 1][x - 1] == 2;
    occ += state[y - 1][x + 1] == 2;
    occ += state[y - 1][x] == 2;
    occ += state[y + 1][x] == 2;

    return occ;
}

struct visibles
{
    std::pair<int, int> s1;
    std::pair<int, int> s2;
    std::pair<int, int> s3;
    std::pair<int, int> s4;
    std::pair<int, int> s5;
    std::pair<int, int> s6;
    std::pair<int, int> s7;
    std::pair<int, int> s8;
};

void compute_visibility(
    const std::array<std::array<char, 100>, 100>& state, 
    std::array<std::array<visibles, 100>, 100>& visibility)
{
    for (int y = 1; y < state.size() - 1; y++)
    {
        for (int x = 1; x < state[y].size() - 1; x++)
        {
            if (state[y][x] == '.') continue;
            int y1 = y;
            int x1 = x;
            bool first = true;
            for (int k = 0; 0 <= y1 && y1 < state.size(); k++)
            {
                visibility[y][x].s1.first = y1;
                visibility[y][x].s1.second = x1;
                if (state[y1][x1] == 1 && !first) 
                {
                    break;
                }
                first = false;
                y1--;
            }

            y1 = y;
            x1 = x;
            first = true;
            for (int k = 0; 0 <= y1 && y1 < state.size(); k++)
            {
                visibility[y][x].s2.first = y1;
                visibility[y][x].s2.second = x1;
                if (state[y1][x1] == 1 && !first) 
                {
                    break;
                }
                y1++;
                first = false;
            }

            y1 = y;
            x1 = x;
            first = true;
            for (int k = 0; 0 <= x1 && x1 < state[y1].size(); k++)
            {
                visibility[y][x].s3.first = y1;
                visibility[y][x].s3.second = x1;
                if (state[y1][x1] == 1 && !first) 
                {
                    break;
                }
                x1--;
                first = false;
            }

            y1 = y;
            x1 = x;
            first = true;
            for (int k = 0; 0 <= x1 && x1 < state[y1].size(); k++)
            {
                visibility[y][x].s4.first = y1;
                visibility[y][x].s4.second = x1;
                if (state[y1][x1] == 1 && !first) 
                {
                    break;
                }
                x1++;
                first = false;
            }

            y1 = y;
            x1 = x;
            first = true;
            for (int k = 0; 0 <= y1 && y1 < state.size() && 0 <= x1 && x1 < state[y1].size(); k++)
            {
                visibility[y][x].s5.first = y1;
                visibility[y][x].s5.second = x1;
                if (state[y1][x1] == 1 && !first) 
                {
                    break;
                }
                y1++;
                x1++;
                first = false;
            }

            y1 = y;
            x1 = x;
            first = true;
            for (int k = 0; 0 <= y1 && y1 < state.size() && 0 <= x1 && x1 < state[y1].size(); k++)
            {
                visibility[y][x].s6.first = y1;
                visibility[y][x].s6.second = x1;
                if (state[y1][x1] == 1 && !first) 
                {
                    break;
                }
                y1--;
                x1++;
                first = false;
            }

            y1 = y;
            x1 = x;
            first = true;
            for (int k = 0; 0 <= y1 && y1 < state.size() && 0 <= x1 && x1 < state[y1].size(); k++)
            {
                visibility[y][x].s7.first = y1;
                visibility[y][x].s7.second = x1;
                if (state[y1][x1] == 1 && !first) 
                {
                    break;
                }
                y1++;
                x1--;
                first = false;
            }

            y1 = y;
            x1 = x;
            first = true;
            for (int k = 0; 0 <= y1 && y1 < state.size() && 0 <= x1 && x1 < state[y1].size(); k++)
            {
                visibility[y][x].s8.first = y1;
                visibility[y][x].s8.second = x1;
                if (state[y1][x1] == 1 && !first) 
                {
                    break;
                }
                y1--;
                x1--;
                first = false;
            }
        }
    }
}

int visible_occupied(
    int x,
    int y,
    const std::array<std::array<char, 100>, 100>& state,
    const std::array<std::array<visibles, 100>, 100>& visibility)
{
    int occ = 0;

    int y1 = visibility[y][x].s1.first;
    int x1 = visibility[y][x].s1.second;
    occ += state[y1][x1] == 2;
        
    int y2 = visibility[y][x].s2.first;
    int x2 = visibility[y][x].s2.second;
    occ += state[y2][x2] == 2;

    int y3 = visibility[y][x].s3.first;
    int x3 = visibility[y][x].s3.second;
    occ += state[y3][x3] == 2;

    int y4 = visibility[y][x].s4.first;
    int x4 = visibility[y][x].s4.second;
    occ += state[y4][x4] == 2;

    int y5 = visibility[y][x].s5.first;
    int x5 = visibility[y][x].s5.second;
    occ += state[y5][x5] == 2;

    int y6 = visibility[y][x].s6.first;
    int x6 = visibility[y][x].s6.second;
    occ += state[y6][x6] == 2;

    int y7 = visibility[y][x].s7.first;
    int x7 = visibility[y][x].s7.second;
    occ += state[y7][x7] == 2;

    int y8 = visibility[y][x].s8.first;
    int x8 = visibility[y][x].s8.second;
    occ += state[y8][x8] == 2;

    return occ;
}

#define GRID 100

int main(int arg, char* argv[])
{   
    auto begin = std::chrono::high_resolution_clock::now();
    std::ifstream file { std::string(argv[1]) };

    // 0 == floor
    // 1 == empty seat
    // 2 == occupied seat
    std::array<std::array<char, 100>, 100> original;
    std::array<std::array<char, 100>, 100> adj;
    std::array<std::array<visibles, 100>, 100> visibility;
    std::string line;

    int y = 1;
    while (getline(file, line))
    {
        for (int i = 0; i < line.size(); i++)
        {
            original[y][i + 1] = line.at(i) == 'L';
        }
        y++;
    }    
    

    adj = std::array<std::array<char, 100>, 100>(original);
    bool changed = true;
    int p1 = 0;
    while (changed)
    {
        changed = false;
        std::array<std::array<char, 100>, 100> adj_new(adj);
        for (int y = 1; y < adj.size() - 1; y++)
        {
            for (int x = 1; x < adj[y].size() - 1; x++)
            {
                if (adj[y][x] == 0) continue;
                int occ = occupied(x, y, adj);
                if (adj[y][x] == 1)
                {
                    if (occ == 0)
                    {
                        adj_new[y][x] = 2;
                    }
                }
                if (adj[y][x] == 2)
                {
                    if (occ >= 4)
                    {
                        adj_new[y][x] = 1;
                    }
                }

                changed |= adj[y][x] != adj_new[y][x];
            }
        }

        if (changed)
        {
            adj = adj_new;
        }
    }

    for (int y = 1; y < adj.size() - 1; y++)
    {
        for (int x = 1; x < adj[y].size() - 1; x++)
        {
            p1 += adj[y][x] == 2;
        }
    }

    adj = std::array<std::array<char, 100>, 100>(original);
    compute_visibility(adj, visibility);
    changed = true;
    int p2 = 0;
    while (changed)
    {
        changed = false;
        std::array<std::array<char, 100>, 100> adj_new(adj);
        for (int y = 1; y < adj.size() - 1; y++)
        {
            for (int x = 1; x < adj[y].size() - 1; x++)
            {
                if (adj[y][x] == 0) continue;
                int occ = visible_occupied(x, y, adj, visibility);
                if (adj[y][x] == 1)
                {
                    if (occ == 0)
                    {
                        adj_new[y][x] = 2;
                    }
                }
                if (adj[y][x] == 2)
                {
                    if (occ >= 5)
                    {
                        adj_new[y][x] = 1;
                    }
                }

                changed |= adj[y][x] != adj_new[y][x];
            }
        }

        if (changed)
        {
            adj = adj_new;
        }
    }


    for (int y = 1; y < adj.size() - 1; y++)
    {
        for (int x = 1; x < adj[y].size() - 1; x++)
        {
            p2 += adj[y][x] == 2;
        }
    }

    std::cout << p1 << "\n";
    std::cout << p2 << "\n";
    std::cout << duration.count() << "\n";
}  