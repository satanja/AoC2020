#include <iostream>
#include <sstream>
#include <string>
#include <unordered_set>
#include <vector>

#include "stefan.h"

void aoc01(const char *arr, int len, unsigned char **output) {
    std::string in(arr, arr + len);
    std::istringstream cin(in);
    std::ostringstream cout((char*) *output);
    int x;
    std::unordered_set<int> X;
    const int target = 2020;
    // goto part2;
part1:
    while (cin >> x)
    {
        if (X.contains(2020 - x))
        {
            cout << (2020 - x) * x << " ";
            goto part2;
        }
        else 
        {
            X.insert(x);
        }
    }
part2:
    cin.seekg(0);
    std::vector<int> Y;
    while (cin >> x)
    {
        for (int i = 0; i < Y.size(); i++)
        {
            for (int j = i + 1; j < Y.size(); j++)
            {
                if (x + Y[i] + Y[j] == 2020)
                {
                    cout << x * Y[i] * Y[j] << "\n";
                    return;
                }
            }
        }
        Y.push_back(x);
    }
}
