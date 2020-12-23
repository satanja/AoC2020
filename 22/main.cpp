#include <fstream>
#include <sstream>
#include <iostream>
#include <string>
#include <utility>
#include <vector>
#include <deque>
#include <set>

std::pair<bool, std::deque<int>> recursive_game(std::deque<int> deck1, std::deque<int> deck2)
{
    std::set<std::deque<int>> conf_p1;
    std::set<std::deque<int>> conf_p2;

    while (!deck1.empty() && !deck2.empty())
    {
        if (conf_p1.contains(deck1) || conf_p2.contains(deck2))
        {
            return std::make_pair(true, deck1);
        }
        else 
        {
            conf_p1.insert(deck1);
            conf_p2.insert(deck2);
        }
        int a = deck1.front();
        deck1.pop_front();

        int b = deck2.front();
        deck2.pop_front();

        if (deck1.size() >= a && deck2.size() >= b)
        {
            // recurse
            std::deque<int> rdeck1;
            for (int i = 0; i < a; i++)
            {
                rdeck1.push_back(deck1[i]);
            }
            std::deque<int> rdeck2;
            for (int i = 0; i < b; i++)
            {
                rdeck2.push_back(deck2[i]);
            }

            if (recursive_game(rdeck1, rdeck2).first)
            {
                deck1.push_back(a);
                deck1.push_back(b);
            }
            else 
            {
                deck2.push_back(b);
                deck2.push_back(a);
            }
        }
        else 
        {
            if (a > b)
            {
                deck1.push_back(a);
                deck1.push_back(b);
            }
            else 
            {
                deck2.push_back(b);
                deck2.push_back(a);
            }
        }
    }
    
    if (!deck1.empty())
    {
        return std::make_pair(true, deck1);
    }
    else 
    {
        return std::make_pair(false, deck2);
    }
}

int main(int arg, char* argv[])
{
    std::ifstream file { std::string(argv[1]) };
    std::string line;
    getline(file, line);
    std::deque<int> player1;
    std::deque<int> player2;
    std::deque<int>* current_player = &player1;
    while(getline(file, line))
    {
        if (line == "")
        {
            current_player = &player2;
            getline(file, line);
        }
        else 
        {
            int k = 0;
            for (int i = 0; i < line.size(); i++)
            {
                k *= 10;
                k += line.at(i) - '0';
            }
            current_player->push_back(k);
        }
    }

    std::deque<int> player12(player1);
    std::deque<int> player22(player2);

    // part 1
    while (!player1.empty() && !player2.empty())
    {
        int a = player1.front();
        player1.pop_front();
        int b = player2.front();
        player2.pop_front();

        if (a > b)
        {
            player1.push_back(a);
            player1.push_back(b);
        }
        else 
        {
            player2.push_back(b);
            player2.push_back(a);
        }
    }

    std::deque<int>* winner = &player1;
    if (player1.empty())
    {
        winner = &player2;
    }
    
    int cards = winner->size();
    int64_t p1 = 0;
    for (int i = 0; i < winner->size(); i++)
    {
        p1 += (cards - i) * winner->at(i);
    }

    int64_t p2 = 0;
    std::deque<int>winner2 = recursive_game(player12, player22).second;
    for (int i = 0; i < winner2.size(); i++)
    {
        p2 += (cards - i) * winner2[i];
    }

    
    std::cout << p1 << "\n";
    std::cout << p2 << "\n";
}