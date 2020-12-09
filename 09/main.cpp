#include <fstream>
#include <sstream>
#include <iostream>
#include <string>
#include <unordered_set>
#include <deque>
#include <vector>
#include <algorithm>

int main(int arg, char* argv[])
{
    std::ifstream file { std::string(argv[1]) };

    std::deque<unsigned long long> queue;
    std::unordered_set<unsigned long long> hist;
    std::vector<unsigned long long> list;
    // reading input
    
    std::string line;

    int pre = 0;
    unsigned long long p1 = 0;
    int index = 0;
    while (getline(file, line))
    {
        unsigned long long num = std::stoull(line);
        if (pre < 25)
        {
            hist.insert(num);
            queue.push_back(num);
            pre++;
        }
        else 
        {
            bool okay = false;
            for (auto const x : queue)
            {
                okay |= hist.contains(num - x);
            }
            if (okay)
            {
                unsigned long long front = queue.front();
                hist.erase(front);
                queue.pop_front();

                hist.insert(num);
                queue.push_back(num);
            }
            else 
            {
                if (p1 == 0) {
                    p1 = num;
                    index = list.size();
                } 
            }
        }
        list.push_back(num);
    }

    unsigned long long p2 = 0;

    for (int i = 0; i < index; i++)
    {
        unsigned long long sum = 0;
        int j = i;
        unsigned long long min = list[j];
        unsigned long long max = list[j];
        while (sum < p1)
        {
            min = std::min(list[j], min);
            max = std::max(list[j], max);
            sum += list[j];
            j++;
        }

        if (sum == p1)
        {
            p2 = min + max;
        }
    }

    std::cout << p1 << "\n";
    std::cout << p2 << "\n";
}  