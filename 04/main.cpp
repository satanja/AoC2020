#include <algorithm>
#include <array>
#include <fstream>
#include <iostream>
#include <string>

int main(int arg, char *argv[])
{
    std::ifstream file{std::string(argv[1])};

    std::string str;
    bool space = false;
    bool consume = false;
    bool f = false;
    std::array<char, 8> fields;
    char field;
    int count = 0;
    int correct = 0;
    while (getline(file, str))
    {
        if (str.size() == 2)
        {
            int k = 0;
            if (count == 8)
            {
                k = 1;
            }
            else 
            {
                int delta = 0;
                for (int i = 0; i < fields.size(); i++)
                {
                    if (fields[i] == 'a')
                    {
                        delta += 1;
                        break;
                    }
                }
                k = (count - delta) >= 7;
            }
            correct += k;
            count = 0;

            for (int i = 0; i < fields.size(); i++)
            {
                fields[i] = 0;
            }
        }
        else
        {
            for (auto const &c : str)
            {
                if (c == ' ')
                {
                    fields[count++] = field;
                    field = 0;
                    consume = false;
                    f = false;
                } else if (consume)
                {
                    consume = c != ' ';
                }
                else
                {
                    if (c == ':')
                    {
                        consume = true;
                    }
                    else if (c == 'c' && !f)
                    {
                        field = 'a';
                    }
                    else if (!f)
                    {
                        field = c;
                    }
                    f = true;
                }
            }
        }
    }
    std::cout << correct << "\n";
}