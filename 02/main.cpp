#include <iostream>
#include <string>
#include <sstream>

#include "stefan.h"

void aoc02(const char *arr, int len, unsigned char **out) {
    std::string in(arr, arr + len);
    std::istringstream cin(in);
    std::ostringstream cout((char*) *out);

    int min = -1;
    int max = -1;
    char k;
    int count = 0;
    int correct1 = 0;
    int correct2 = 0;

    bool read_range = false;
    bool first = true;
    bool second = false;
    bool is_character = false;
    bool is_string = false;
    std::string line;
    while (getline(cin, line))
    {
        int num = 0;
        int pos = 1;
        bool a = false;
        bool b = false;
        for (auto const &c : line)
        {
            if (is_character)
            {
                k = c;
                is_character = false;
            }
            else if (0 <= c - '0' && c - '0' <= 9)
            {
                num *= 10;
                num += c - '0';
            }
            else if (c == '-')
            {
                min = num;
                num = 0;
            }
            else if (c == ' ' && first)
            {
                max = num;
                num = 0;
                first = false;
                second = true;
                is_character = true;
            }
            else if (c == ' ' && second)
            {
                is_string = true;
            }
            else if (is_string)
            {
                if (c == k)
                {
                    if (pos == min)
                    {
                        a = true;
                    }
                    if (pos == max)
                    {
                        b = true;
                    }
                    count++;
                }
                pos++;
            }
        }
        if (min <= count && count <= max)
        {
            correct1++;
        }
        if (/*min <= count && count <= max */ a ^ b)
        {
            correct2++;
        }
        // reset
        count = 0;
        read_range = false;
        first = true;
        second = false;
        is_character = false;
        is_string = false;
    }
    // cout << correct1 << "\n";
    // cout << correct2 << "\n";
}