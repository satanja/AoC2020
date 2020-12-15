#include <string>
#include <unordered_map>
#include <iostream>
#include <fstream>
#include <vector>
int main(int arg, char* argv[])
{
    std::ifstream file { std::string(argv[1]) };
    std::string line;

    std::vector<int> starting;
    getline(file, line);
    int k = 0;
    for (int i = 0; i < line.size(); i++)
    {
        if (line.at(i) != ',')
        {
           k *= 10;
           k += line.at(i) - '0';
        }
        else 
        {
            starting.push_back(k);
            k = 0;
        }
    }
    starting.push_back(k);

    int turn = 1;
    std::unordered_map<int, std::pair<int, int>> history;
    for (int num : starting)
    {
        history.insert(std::make_pair(num, std::make_pair(turn, turn)));
        turn++;
    }
    int last_num = starting[starting.size() - 1];
    bool duplicate = false;
    int p1 = 0;
    while (turn <= 30000000)
    {   
        if (!duplicate)
        {
            last_num = 0;
            duplicate = history.contains(last_num);
            if (duplicate)
            {
                history.at(last_num).first = history.at(last_num).second;
                history.at(last_num).second = turn;
            }
            else
            {
                history.insert(std::make_pair(last_num, std::make_pair(turn, turn)));
            }
        }
        else 
        {
            last_num = (turn - 1) - history.at(last_num).first;
            duplicate = history.contains(last_num);
            if (duplicate)
            {
                history.at(last_num).first = history.at(last_num).second;
                history.at(last_num).second = turn;
            }
            else
            {
                history.insert(std::make_pair(last_num, std::make_pair(turn, turn)));
            }
        }
        turn++;
    }
    std::cout << last_num << "\n";
}