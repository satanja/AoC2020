#include <fstream>
#include <string>
#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <map>

#define SIZE 20

struct field
{
    int min1, min2, max1, max2;
    const bool is_valid(int key) const 
    {
        return (min1 <= key && key <= max1) || (min2 <= key && key <= max2);
    }
};

int main(int arg, char* argv[])
{
    std::ifstream file { std::string(argv[1]) };
    std::string line;
    
    bool fields_done = false;
    std::unordered_map<std::string, field> fields;
    std::vector<int> my_ticket(SIZE);
    std::vector<std::vector<int>> tickets;
    std::vector<std::pair<std::string, field>> guess_order;
    while (getline(file, line))
    {   
        if (line == "" && !fields_done)
        {
            fields_done = true;
            getline(file, line);
            getline(file, line);
            int j = 0;
            int k = 0;
            for (int i = 0; i < line.size(); i++)
            {
                if (line.at(i) != ',')
                {
                k *= 10;
                k += line.at(i) - '0';
                }
                else 
                {
                    my_ticket[j++] = k;
                    k = 0;
                }
            }
            my_ticket[j++] = k;
            getline(file, line);
            getline(file, line);
        } else if (fields_done)
        {
            std::vector<int> ticket(SIZE);
            int j = 0;
            int k = 0;
            for (int i = 0; i < line.size(); i++)
            {
                if (line.at(i) != ',')
                {
                k *= 10;
                k += line.at(i) - '0';
                }
                else 
                {
                    ticket[j++] = k;
                    k = 0;
                }
            }
            ticket[j++] = k;
            tickets.push_back(ticket);
        }
        else 
        {
            int i = 0;
            while (line.at(i) != ':')
            {
                i++;
            }
            field f;
            std::string name = line.substr(0, i);

            i += 2;
            int k = 0;
            while (line.at(i) != '-')
            {
                k *= 10;
                k += line.at(i) - '0';
                i++;
            }
            f.min1 = k;
            i++;
            k = 0;
            while (line.at(i) != ' ')
            {
                k *= 10;
                k += line.at(i) - '0';
                i++;
            }
            f.max1 = k;
            i += 4;
            k = 0;
            while (line.at(i) != '-')
            {
                k *= 10;
                k += line.at(i) - '0';
                i++;
            }
            f.min2 = k;
            i++;
            k = 0;
            while (i < line.size())
            {
                k *= 10;
                k += line.at(i) - '0';
                i++;
            }
            f.max2 = k;
            fields.emplace(name, f);
            guess_order.push_back(std::make_pair(name, f));
        }
    }

    int64_t p1 = 0;
    std::vector<std::vector<int>> correct_tickets;
    for (auto const ticket : tickets)
    {   
        bool valid_ticket = true;
        for (auto const& key : ticket)
        {
            bool valid = false;
            for (auto const& [k, f] : fields)
            {
                valid |= f.is_valid(key);
            }
            p1 += (!valid) * key;
            valid_ticket &= valid;
        }
        if (valid_ticket)
        {
            correct_tickets.push_back(ticket);
        }
    }

    std::unordered_set<int> completed_keys;
    std::map<int, std::pair<std::string, field>> order;
    while (fields.size() != 0)
    {
        for (auto const [name, field] : fields)
        {   
            // check on how many keys field is correct
            int count = 0;
            int last_valid_key = 0;
            for (int i = 0; i < guess_order.size(); i++)
            {   
                if (completed_keys.contains(i)) continue;
                bool valid = true;
                for (int j = 0; j < correct_tickets.size(); j++)
                {
                    valid &= field.is_valid(correct_tickets[j][i]);
                }
                if (valid)
                {
                    last_valid_key = i;
                    count++;
                }
            }
            if (count == 1)
            {
                fields.erase(name);
                order.insert(std::make_pair(last_valid_key, std::make_pair(name, field)));
                completed_keys.insert(last_valid_key);
                break;
            }
        }
    }

    uint64_t p2 = 1;
    for (auto const& [i, pair] : order)
    {
        if (pair.first.size() >= 9 && pair.first.substr(0, 9) == "departure")
        {
            p2 *= my_ticket[i];
        }
    }
    std::cout << p1 << "\n";
    std::cout << p2 << "\n";
}