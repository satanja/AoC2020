#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <sstream>
#include "stefan.h"

void aoc05(const char *arr, int len, unsigned char **out)
{
    std::string in(arr, arr + len);
    std::istringstream file(in);
    std::ostringstream cout((char*) *out);

    std::string str;
    std::vector<int> seats;
    while (getline(file, str))
    {
        int k = 0;
        // row
        for (int i = 0; i < 7; i++)
        {
            k *= 2;
            k += str.at(i) == 'B';
        }
        // column 
        for (int i = 7; i < 10; i++)
        {
            k *= 2;
            k += str.at(i) == 'R';
        }
        // todo compute k
        seats.push_back(k);
    }
    sort(seats.begin(), seats.end());
    int my_seat = 0;
    for (int i = 0; i < seats.size() - 1; i++)
    {
        if (seats[i] + 1 < seats[i + 1])
        {
            my_seat = seats[i] + 1;
            break;
        }
    }
    std::cout << seats[seats.size() - 1] << "\n";
    std::cout << my_seat << "\n";
}