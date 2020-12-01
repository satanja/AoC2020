#include <iostream>
#include <unordered_set>
int main()
{
    int x;
    std::unordered_set<int> X;
    const int target = 2020;
    goto part2;
part1:
    while (std::cin >> x)
    {
        if (X.contains(2020 - x))
        {
           std::cout << (2020 - x) * x << "\n";
           return 0;
        }
        else 
        {
            X.insert(x);
        }
    }
part2:

    std::vector<int> Y;
    while (std::cin >> x)
    {
        for (int i = 0; i < Y.size(); i++)
        {
            for (int j = i + 1; j < Y.size(); j++)
            {
                if (x + Y[i] + Y[j] == 2020)
                {
                    std::cout << x * Y[i] * Y[j] << "\n";
                    return 0;
                }
            }
        }
        Y.push_back(x);
    }
}