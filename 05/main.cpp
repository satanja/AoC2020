#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

int main(int arg, char* argv[])
{
    std::ifstream file { std::string(argv[1]) };
    

    std::string str;
    int max_id = -1;
    std::vector<int> seats;
    while (getline(file, str))
    {
        int k = 0;
        // row
        for (int i = 0; i < str.size() - 3; i++)
        {
            k |= ((str.at(i) != 'F') << (9 - i));
        }
        // column 
        for (int i = str.size() - 3; i < str.size(); i++)
        {
            k |= ((str.at(i) != 'L') << (9 - i));
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