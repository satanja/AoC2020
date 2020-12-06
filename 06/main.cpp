#include <unordered_set>
#include <unordered_map>
#include <iostream>
#include <fstream>
#include <string>

int main(int arg, char* argv[])
{
    std::fstream file { std::string(argv[1]) };
    std::string line;

    std::unordered_set<char> questions;
    std::unordered_map<char, int> questions2;
    int count1 = 0;
    int count2 = 0;
    int p = 0;
    while (getline(file, line))
    {
        if (line == "")
        {
            count1 += questions.size();
            questions.clear();
            for (auto [k, v] : questions2)
            {
                if (v == p)
                {
                    count2++;
                }
            }
            p = 0;
            questions2.clear();
        }
        else 
        {
            p++;
            for (auto const& c : line)
            {
                questions.insert(c);
                if (questions2.contains(c))
                {
                    questions2.at(c) += 1;
                }
                else 
                {
                    questions2.insert(std::make_pair(c, 1));
                }
            }
        }
    }
    count1 += questions.size();
    for (auto [k, v] : questions2)
    {
        if (v == p)
        {
            count2++;
        }
    }
    std::cout << count1 << "\n";
    std::cout << count2 << "\n";
}