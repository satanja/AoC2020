#include <fstream>
#include <iostream>
#include <string>
#include <vector>

int64_t modulo(int64_t value, int64_t m) {
    int64_t mod = value % (int64_t)m;
    if (mod < 0) {
        mod += m;
    }
    return mod;
}

int64_t inverse(int64_t a, int64_t b)
{
    int64_t old_r = a;
    int64_t r = b;

    int64_t old_s = 1;
    int64_t s = 0;

    int64_t old_t = 0;
    int64_t t = 1;

    int64_t qoutient = 0;
    while (r != 0)
    {
        int64_t temp_old_r = old_r;
        int64_t temp_r = r;
        qoutient = old_r / r;
        old_r = temp_r;
        r = temp_old_r - qoutient * temp_r;

        int64_t temp_old_s = old_s;
        int64_t temp_s = s;
        old_s = temp_s;
        s = temp_old_s - qoutient * temp_s;

        int64_t temp_old_t = old_t;
        int64_t temp_t = t;

        old_t = temp_t;
        t = temp_old_t - qoutient * temp_t;
    }

    return modulo(old_s, b);
}

int main(int arg, char* argv[])
{
    std::ifstream file { std::string(argv[1]) };
    std::string line;
    std::vector<std::pair<int64_t, int64_t>> system;

    int64_t l = 0;
    int64_t t = 0;
    bool first = true;
    int64_t N = 1;
    while (getline(file, line))
    {
        if (first)
        {
            l = std::stoi(line);
            first = false;
        }
        else 
        {
            for (int i = 0; i < line.size(); i++)
            {
                if (line.at(i) == ',') continue;
                if (line.at(i) == 'x')
                {
                    t++;
                }
                else
                {
                    int64_t k = 0;
                    while (i < line.size() && line.at(i) != ',')
                    {
                        k *= 10;
                        k += line.at(i) - '0';
                        i++;
                    }
                    system.emplace_back(modulo(-t, k), k);
                    N *= k;
                    t++;
                }
            }
        }
    }

    int64_t result = 0;
    int64_t min_t = l + 1;
    int64_t id = 0;
    for (const auto& eq : system)
    {
        int64_t ai = eq.first;
        int64_t ni = eq.second; 
        
        if (std::ceil((double) l / (double) ni) - ni < min_t)
        {
            min_t = std::ceil((double) l / (double) ni) - ni;
            id = ni;
        }
        auto q = inverse(N / ni, ni);
        result += ai * (N / ni) * q;
    }

    std::cout << id * min_t << std::endl;
    std::cout << modulo(result, N) << std::endl;
}