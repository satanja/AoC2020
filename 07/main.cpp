#include <fstream>
#include <sstream>
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>
#include <queue>

struct edge
{
    int weight;
    int target;

    edge(int w, int t)
    {
        weight = w;
        target = t;
    }
};

int recursive(int start, const std::vector<std::vector<edge>>& adj)
{
    int bags = 0;
    for (auto const& e : adj[start])
    {
        bags += e.weight + e.weight * recursive(e.target, adj);
    }

    return bags;
}

int main(int arg, char* argv[])
{
    std::ifstream file { std::string(argv[1]) };


    std::vector<std::vector<edge>> adj;
    std::vector<std::vector<edge>> adj_reverse;
    std::unordered_map<std::string, int> map;
    map.emplace("shiny gold", 0);
    adj.push_back(std::vector<edge>());
    adj_reverse.push_back(std::vector<edge>());

    int current_id = 1;

    
    std::string line;
    while (getline(file, line))
    {
        std::stringstream ss(line);
        
        std::string b1;
        std::string b2;

        ss >> b1 >> b2;

        int t = 0;
        if (map.contains(b1 + " " + b2))
        {
            t = map.at(b1 + " " + b2);
        }
        else 
        {
            t = current_id;
            map.emplace(b1 + " " + b2, current_id++);
            adj.push_back(std::vector<edge>());
            adj_reverse.push_back(std::vector<edge>());
        }

        std::string bs;
        ss >> bs;

        std::string contain;
        ss >> contain;

        std::string num;
        ss >> num;

        if (num.at(0) != 'n')
        {
            while (true) {
                int w = std::stoi(num);
                ss >> b1 >> b2;
                int v = 0;
                if (map.contains(b1 + " " + b2))
                {
                    v = map.at(b1 + " " + b2);
                }
                else 
                {
                    v = current_id;
                    map.emplace(b1 + " " + b2, current_id++);
                    adj.push_back(std::vector<edge>());
                    adj_reverse.push_back(std::vector<edge>());
                }
                adj[v].emplace_back(w, t);
                adj_reverse[t].emplace_back(w, v);

                std::string eol;
                ss >> eol;
                if (eol.back() == '.')
                {
                    break;
                }
                else
                {
                    ss >> num;
                }
                
            }
        }
    }

    std::vector<char> discovered(adj.size());
    int p1 = 0; 
    std::queue<int> queue;
    queue.push(0);
    discovered[0] = true;

    while (!queue.empty())
    {
        int v = queue.front();
        queue.pop();
        for (auto e : adj[v])
        {
            if (!discovered[e.target])
            {
                queue.push(e.target);
                discovered[e.target] = true;
                p1++;
            }
        }
    }

    std::cout << p1 << "\n";
    std::cout << recursive(0, adj_reverse) << "\n";
}