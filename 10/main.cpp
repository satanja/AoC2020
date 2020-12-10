#include <fstream>
#include <sstream>
#include <iostream>
#include <string>
#include <unordered_set>
#include <vector>
#include <algorithm>
#include <array>
#include <queue>

int main(int arg, char* argv[])
{
    std::ifstream file { std::string(argv[1]) };

    std::vector<std::vector<int>> adj;
    std::vector<int> adapters;
    int max_jolt = 0;

    std::string line;
    while (getline(file, line))
    {   
        int jolt = std::stoi(line);
        max_jolt = std::max(jolt, max_jolt);
        adapters.push_back(jolt);
    }

    adj.resize(max_jolt, std::vector<int>(0));
    for (auto jolt : adapters)
    {   
        for (int i = std::max(0, jolt - 3); i < jolt; i++)
        {
            adj[i].push_back(jolt);
        }
    }

    for (auto& list : adj)
    {
        sort(list.begin(), list.end());
    }

    int curr_jolt = 0;
    int diff1 = 0;
    int diff3 = 0;

    std::vector<int> covered;
    while (curr_jolt < max_jolt)
    {
        int size = adj[curr_jolt].size();
        if (adj[curr_jolt][0] - curr_jolt == 1)
        {
            diff1++;
        }
        else if (adj[curr_jolt][0] - curr_jolt == 3)
        {
            diff3++;
        }

        for (int i = 0; i < size - 1; i++)
        {
            covered.push_back(adj[curr_jolt][i]);
            if (adj[curr_jolt][i + 1] - adj[curr_jolt][i] == 1)
            {
                diff1++;
            }
            else if (adj[curr_jolt][i + 1] - adj[curr_jolt][i] == 3)
            {
                diff3++;
            }
        }
        covered.push_back(adj[curr_jolt][size - 1]);

        curr_jolt = adj[curr_jolt][size - 1];
    }
    diff3++; // last adapter
    int p1 = diff1 * diff3;

    std::vector<uint64_t> dp_paths(max_jolt + 1);
    dp_paths[max_jolt] = 1;
    for (int i = max_jolt - 1; i >= 0; i--)
    {
        uint64_t paths = 0;
        for (int x : adj[i])
        {
            paths += dp_paths[x];
        }
        dp_paths[i] = paths;
    }
    uint64_t p2 = dp_paths[0];
    std::cout << p1 << "\n";
    std::cout << p2 << "\n";
}  