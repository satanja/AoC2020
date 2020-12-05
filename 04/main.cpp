#include <algorithm>
#include <array>
#include <fstream>
#include <sstream>
#include <iostream>
#include <string>
#include <regex>

struct passport
{
    int byr = 0;
    int iyr = 0;
    int eyr = 0;
    std::string cid = "";
    std::string hgt = "";
    std::string hcl = "";
    std::string ecl = "";
    std::string pid = "";

    bool is_complete()
    {
        return
        byr != 0 &&
        iyr != 0 &&
        eyr != 0 &&
        pid != "" &&
        hgt != "" &&
        hcl != "" &&
        ecl != "";
    }

    bool is_valid()
    {
        bool valid_ints =
        (1920 <= byr && byr <= 2002) &&
        (2010 <= iyr && iyr <= 2020) &&
        (2020 <= eyr && eyr <= 2030);

        bool valid_hgt = false;
        if (hgt != "") {
            if (hgt.substr(hgt.size() - 2) == "cm")
            {
                int l = std::stoi(hgt.substr(0, hgt.size() - 2));
                valid_hgt = (150 <= l && l <= 193);
            }
            else if (hgt.substr(hgt.size() - 2, 2) == "in")
            {
                int l = std::stoi(hgt.substr(0, hgt.size() - 2));
                valid_hgt = (59 <= l && l <= 76);
            }
        }
        
        bool valid_hcl = false;
        if (hcl.size() == 7)
        {
            auto const query = std::regex("^[0-9a-f]{6}");
            valid_hcl = std::regex_match(hcl.substr(1), query) && hcl.at(0) == '#';
        }        

        bool valid_ecl = (ecl == "amb" ||
                          ecl == "blu" ||
                          ecl == "gry" ||
                          ecl == "grn" ||
                          ecl == "hzl" ||
                          ecl == "oth");

        bool valid_pid = false;
        if (pid.size() == 9)
        {
            auto const query = std::regex("^[0-9]{9}");
            valid_pid = std::regex_match(pid, query);
        }

        return valid_ints && valid_hgt && valid_hcl && valid_ecl && valid_pid;
    }

    void clear()
    {
        byr = 0;
        iyr = 0;
        eyr = 0;
        cid = "";
        hgt = "";
        hcl = "";
        ecl = "";
        pid = ""; 
    }
};

int main(int arg, char *argv[])
{
    std::ifstream file{std::string(argv[1])};

    std::string line;
    
    passport p;
    int p1 = 0;
    int p2 = 0;
    while (getline(file, line))
    {
        if (line == "")
        {
            p1 += p.is_complete();
            p2 += p.is_valid();
            if (p.is_valid())
            {
                std::cout << "true\n";
            }
            else 
            {
                std::cout << "false\n";
            }
            p.clear();
        }
        else
        {
            std::stringstream ss(line);
            std::string word;
            while (ss >> word)
            {
                std::string field = word.substr(0, 3);
                if (field == "byr")
                {
                    p.byr = std::stoi(word.substr(4)); 
                }
                else if (field == "iyr")
                {
                    p.iyr = std::stoi(word.substr(4)); 
                }
                else if (field == "eyr")
                {
                    p.eyr = std::stoi(word.substr(4));
                }
                else if (field == "hgt")
                {
                    p.hgt = word.substr(4);
                }
                else if (field == "hcl")
                {
                    p.hcl = word.substr(4);
                }
                else if (field == "ecl")
                {
                    p.ecl = word.substr(4);
                }
                else if (field == "pid")
                {
                    p.pid = word.substr(4);
                }
                else if (field == "cid")
                {
                    p.cid = word.substr(4);
                }
            }
        }
    }
    p1 += p.is_complete();
    p2 += p.is_valid();

    std::cout << p1 << "\n";
    std::cout << p2 << "\n";
}