#include <iostream>
#include <sstream>
#include <string>
#include <unordered_set>
#include <vector>
#include <bitset>
#include <array>
#include "stefan.h"

template<size_t k>
class array_vector
{
private:
    std::array<int, k> arr;
    int head = 0;
public:
    size_t size() 
    {
        return head;
    }

    size_t capacity()
    {
        return k;
    }

    int operator[](int index)
    {
        return arr[index];
    }

    void push_back(int val)
    {
        if (size() == arr.size()) return;
        arr[head] = val;
        head++;
    }
};

void aoc01(const char *arr, int len, unsigned char **out) {
    std::string in(arr, arr + len);
    std::istringstream cin(in);
    std::ostringstream cout((char*) *out);
    int x;
    std::bitset<2020> X;
    const int target = 2020;
    while (cin >> x)
    {
        if (X[2020 - x])
        {
            cout << (2020 - x) * x << " ";
            goto part2;
        }
        else 
        {
            X[x] = true;
        }
    }
part2:
    X.reset();
    cin.seekg(0);
    array_vector<2020> Y;

    while (cin >> x)
    {
        for (int i = 0; i < Y.size(); i++)
        {   
            if (2020 - x - Y[i] <= 0) continue;
            if (X[2020 - x - Y[i]])
            {
                std::cout << x * Y[i] * (2020 - x - Y[i]) << "\n";
                return;
            }
        }
        Y.push_back(x);
        X[x] = true;
    }
}
