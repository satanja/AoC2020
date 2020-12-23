#include <fstream>
#include <sstream>
#include <iostream>
#include <string>
#include <utility>
#include <vector>
#include <deque>
#include <set>
#include <array>
#include <algorithm>

struct cup
{
    int64_t value;
    cup()
    {

    }
    
    cup(int64_t val)
    {
        value = val;
    }

    cup* next;
    cup* prev;
};

uint64_t part2(const std::string& line)
{
    cup* root = nullptr;
    cup* front = nullptr;
    std::vector<cup*> loc(1000000 + 1);
    for (int i = 0; i < line.size(); i++)
    {
        if (!front)
        {
            front = new cup(line.at(i) - '0');
            root = front;
        }
        else 
        {
            cup* c = new cup(line.at(i) - '0');
            front->next = c;
            c->prev = front;
            front = c;
        }
        loc[front->value] = front;
    }
    for (int64_t i = line.size() + 1; i < loc.size(); i++)
    {
        cup* c = new cup(i);
        front->next = c;
        c->prev = front;
        front = c;
        loc[front->value] = front;
    }
    front->next = root;
    root->prev = front;
    front = root;

    int rounds = 10000000;
    while (rounds > 0)
    {
        cup* c1 = front->next;
        cup* c2 = c1->next;
        cup* c3 = c2->next;
        cup* b = c3->next;
        front->next = b;

        int d = front->value - 1;
        if (d == 0)
        {
            d = 1000000;
        }
        while (d == c1->value || d == c2->value || d == c3->value)
        {
            if (d == 1)
            {
                d = 1000000;
            }
            else 
            {
                d--;
            }
        }

        cup* dest = loc[d];
        cup* dnext = dest->next;
        dest->next = c1;
        c3->next = dnext;
        front = front->next;
        rounds--;
    }

    cup* one = loc[1];
    cup* a = one->next;
    cup* b = a->next;
    return a->value * b->value;
}

int main(int arg, char* argv[])
{
    std::ifstream file { std::string(argv[1]) };
    std::string line;
    getline(file, line);

    std::vector<cup*> loc(line.size() + 1);
    cup* root = nullptr;
    cup* front = nullptr;
    for (int i = 0; i < line.size(); i++)
    {
        if (!front)
        {
            front = new cup(line.at(i) - '0');
            root = front;
        }
        else 
        {
            cup* c = new cup(line.at(i) - '0');
            front->next = c;
            c->prev = front;
            front = c;
        }
        loc[front->value] = front;
    }
    front->next = root;
    root->prev = front;
    front = root;

    int rounds = 100;
    while (rounds > 0)
    {
        cup* c1 = front->next;
        cup* c2 = c1->next;
        cup* c3 = c2->next;
        cup* b = c3->next;
        front->next = b;

        int d = front->value - 1;
        if (d == 0)
        {
            d = 9;
        }
        while (d == c1->value || d == c2->value || d == c3->value)
        {
            if (d == 1)
            {
                d = 9;
            }
            else 
            {
                d--;
            }
        }

        cup* dest = loc[d];
        cup* dnext = dest->next;
        dest->next = c1;
        c3->next = dnext;
        front = front->next;
        rounds--;
    }
    front = loc[1]->next;
    std::string p1;
    for (int i = 0; i < 8; i++)
    {
        p1.push_back(front->value + '0');
        front = front->next;
    }     

    // part 2
    uint64_t p2 = part2(line);
    std::cout << p1 << "\n"; 
    std::cout << p2 << "\n"; 
}