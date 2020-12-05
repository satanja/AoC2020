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
        int k = -1;
        int min_r = 0;
        int max_r = 127;
        int min_c = 0;
        int max_c = 7;
        int r = 1;
        int c = 1;

        // row
        for (int i = 0; i < str.size() - 3; i++)
        {
            if (str.at(i) == 'F')
            {
                max_r = (min_r + max_r) / 2;
            }
            else
            {
                min_r = (min_r + max_r) / 2 + 1;
            }
        }
        r = max_r;

        // column 
        for (int i = str.size() - 3; i < str.size(); i++)
        {
            if (str.at(i) == 'L')
            {
                max_c = (min_c + max_c) / 2;
            }
            else
            {
                min_c = (min_c + max_c) / 2 + 1;
            }
        }
        c = min_c;

        // todo compute k
        k = r * 8 + c;
        if (k > max_id)
        {
            max_id = k;
        }
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
    std::cout << max_id << "\n";
    std::cout << my_seat << "\n";
}