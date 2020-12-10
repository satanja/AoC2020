#include <fstream>
#include <sstream>
#include <iostream>
#include <string>
#include <unordered_set>
#include <vector>
#include <algorithm>
#include <array>
#include "stefan.h"

void aoc09(const char *arr, int len, unsigned char **out)
{
    std::string in(arr, arr + len);
    std::istringstream file(in);
    std::ostringstream cout((char*) *out);
    std::string line;

    std::array<unsigned long long, 25> queue;
    std::unordered_set<unsigned long long> hist;
    std::vector<unsigned long long> list;
    // reading input

    int pre = 0;
    unsigned long long p1 = 0;
    int index = 0;
    int head = 0;
    int tail = 0;
    while (getline(file, line))
    {
        unsigned long long num = std::stoull(line);
        if (pre < 25)
        {
            hist.insert(num);
            queue[pre] = num;
            pre++;
        }
        else 
        {
            bool okay = false;
            for (auto const x : queue)
            {
                if (hist.contains(num - x))
                {
                    okay = true;
                    break;
                }
            }
            if (okay)
            {
                unsigned long long front = queue[head];
                hist.erase(front);
                hist.insert(num);
                tail = head;
                head = (head + 1) % queue.size();
                queue[tail] = num;
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

    cout << p1 << "\n";
    cout << p2 << "\n";
}  