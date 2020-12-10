#include <fstream>
#include <sstream>
#include <iostream>
#include <string>
#include <vector>
#include "stefan.h"

struct instruction
{
    std::string op;
    int val;
    int count = 0;
};

void aoc08(const char *arr, int len, unsigned char **out)
{
    std::string in(arr, arr + len);
    std::istringstream file(in);
    std::ostringstream cout((char*) *out);
    std::string line;

    std::vector<instruction> instructions;
    std::vector<int> jmps;
    std::vector<int> nops;

    int64_t accumulator = 0;
    int64_t p1 = 0;
    int64_t ptr = 0;
    
    while (getline(file, line))
    {
        instruction x;
        x.op = line.substr(0, 3);
        if (x.op == "jmp")
        {
            jmps.push_back(instructions.size());
        }
        if (x.op == "nop")
        {
            nops.push_back(instructions.size());
        }

        if (line.at(4) == '+')
        {
            x.val = std::stoi(line.substr(5));
        }
        else 
        {
            x.val = std::stoi(line.substr(4));
        }
        instructions.push_back(x);
    }

    while (ptr < instructions.size())
    {
        instruction& curr = instructions[ptr];
        curr.count++;
        if (curr.count == 2)
        {
            p1 = accumulator;
            break;
        }

        if (curr.op == "acc")
        {
            accumulator += curr.val;
            ptr++;
        }
        else if (curr.op == "jmp")
        {
            ptr += curr.val;
        }
        else if (curr.op == "nop")
        {
            ptr++;
        }
    }

    for (auto& x : instructions)
    {
        x.count = 0; 
    }

    int64_t p2 = 0;
    bool terminated = false;
    for (int ins : jmps)
    {
        instruction& x = instructions[ins];
        x.op = "nop";
        terminated = true;
        ptr = 0;
        accumulator = 0;
        while (ptr < instructions.size())
        {
            instruction& curr = instructions[ptr];
            curr.count++;
            if (curr.count == 2)
            {
                p1 = accumulator;
                terminated = false;
                break;
            }

            if (curr.op == "acc")
            {
                accumulator += curr.val;
                ptr++;
            }
            else if (curr.op == "jmp")
            {
                ptr += curr.val;
            }
            else if (curr.op == "nop")
            {
                ptr++;
            }
        }
        if (terminated)
        {
            p2 = accumulator;
            break;
        }
        else 
        {
            x.op = "jmp";
            for (auto& x : instructions)
            {
                x.count = 0; 
            }
        }
    }

    if (!terminated)
    {
        for (int ins : nops)
        {
            instruction& x = instructions[ins];
            x.op = "jmp";
            terminated = true;
            ptr = 0;
            accumulator = 0;
            while (ptr < instructions.size())
            {
                instruction& curr = instructions[ptr];
                curr.count++;
                if (curr.count == 2)
                {
                    p1 = accumulator;
                    terminated = false;
                    break;
                }

                if (curr.op == "acc")
                {
                    accumulator += curr.val;
                    ptr++;
                }
                else if (curr.op == "jmp")
                {
                    ptr += curr.val;
                }
                else if (curr.op == "nop")
                {
                    ptr++;
                }
            }
            if (terminated)
            {
                p2 = accumulator;
                break;
            }
            else 
            {
                for (auto& x : instructions)
                {
                    x.count = 0; 
                }
                x.op = "nop";
            }
        }
    }

    std::cout << p1 << "\n";
    std::cout << p2 << "\n";
}