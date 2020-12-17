#include <fstream>
#include <sstream>
#include <iostream>
#include <string>
#include <utility>
#include <vector>
#include "stefan.h"

int occupied(int x, int y, int z, const std::vector<std::vector<std::vector<int>>>& state)
{
    int occ = 0;
    int count = 0;
    for (int i = -1; i < 2; i++)
    {   
        for (int j = -1; j < 2; j++)
        {
            for (int k = -1; k < 2; k++)
            {
                occ += state[z + i][y + j][x + k];
                count++;
            }
        }
    }
    occ -= state[z][y][x];
    return occ;
}

int four_occupied(int x, int y, int z, int w, const std::vector<std::vector<std::vector<std::vector<int>>>>& state)
{
    int occ = 0;
    int count = 0;
    for (int i = -1; i < 2; i++)
    {   
        for (int j = -1; j < 2; j++)
        {
            for (int k = -1; k < 2; k++)
            {
                for (int l = -1; l < 2; l++)
                {
                    occ += state[z + i][y + j][x + k][w + l];
                    count++;
                }
            }
        }
    }
    occ -= state[z][y][x][w];
    return occ;
}

int main(int arg, char* argv[])
{  
    std::ifstream file { std::string(argv[1]) };
    std::string line;

    int height = 0;
    int width = 0;
    std::vector<std::vector<int>> input;
    while (getline(file, line))
    {
        width = line.size();
        std::vector<int> row(width);
        height++;
        for (int i = 0; i < line.size(); i++)
        {
            if (line.at(i) == '#')
            {
                row[i] = 1;
            }
        }
        input.push_back(row);
    }

    int rounds = 6;
    std::vector<std::vector<std::vector<int>>> state(
        1 + 2 * rounds + 2,
        std::vector<std::vector<int>>(
            height + 2 * rounds + 2,
            std::vector<int>(
                width + 2 * rounds + 2
            )
        )
    );

    std::vector<std::vector<std::vector<std::vector<int>>>> four_state(
        1 + 2 * rounds + 2,
        std::vector<std::vector<std::vector<int>>>(
            height + 2 * rounds + 2,
            std::vector<std::vector<int>>(
                width + 2 * rounds + 2,
                std::vector<int>(
                    1 + 2 * rounds + 2
                )
            )
        )
    );

    int a = rounds + 1;
    int d = rounds + 1;
    for (int b = rounds + 1; b < rounds + 1 + height; b++)
    {
        for (int c = rounds + 1; c < rounds + 1 + width; c++)
        {
            state[a][b][c] = input[b - rounds - 1][c - rounds - 1];
            four_state[a][b][c][d] = input[b - rounds - 1][c - rounds - 1];
        }
    }

    for (int r = 0; r < rounds; r++)
    {
        std::vector<std::vector<std::vector<int>>> new_state(state);
        int b1 = rounds - r;
        int e1 = rounds + 2 + r;
        for (int z = 1; z < state.size() - 1; z++)
        {
            int b2 = rounds + 1 - r;
            int e2 = rounds + 2 + r + height;
            for (int y = b2; y < e2; y++)
            {
                int b3 = rounds - r;
                int e3 = rounds + 2 + r + width;
                for (int x = b3; x < e3; x++)
                {
                    int cs = state[z][y][x];
                    int occ = occupied(x, y, z, state);
                    if (cs == 1)
                    {
                        if (occ == 2 || occ == 3)
                        {
                            new_state[z][y][x] = 1;
                        }
                        else 
                        {
                            new_state[z][y][x] = 0;
                        }
                    } else
                    {
                        if (occ == 3)
                        {
                            new_state[z][y][x] = 1;
                        }
                        else 
                        {
                            new_state[z][y][x] = 0;
                        }
                    }
                }
            }
        }

        state = new_state;
    }

    for (int r = 0; r < rounds; r++)
    {
        std::vector<std::vector<std::vector<std::vector<int>>>> new_state(four_state);
        int b1 = 1;
        int e1 = four_state.size() - 1;
        // int b1 = rounds - r; // failed at cheating bounds...
        // int e1 = rounds + 2 + r;
        for (int z = b1; z < e1; z++)
        {
            int b2 = 1;
            int e2 = four_state[z].size() - 1;
            // int b2 = rounds + 1 - r;
            // int e2 = rounds + 2 + r + height;
            for (int y = b2; y < e2; y++)
            {
                int b3 = 1;
                int e3 = four_state[z][y].size() - 1;
                // int b3 = rounds - r;
                // int e3 = rounds + 2 + r + width;
                for (int x = b3; x < e3; x++)
                {
                    int b4 = 1;
                    int e4 = four_state[z][y][x].size() - 1;
                    // int b4 = rounds - r;
                    // int e4 = rounds + 2 + r;
                    for (int w = b4; w < e4; w++)
                    {
                        int cs = four_state[z][y][x][w];
                        int occ = four_occupied(x, y, z, w, four_state);
                        if (cs == 1)
                        {
                            if (occ == 2 || occ == 3)
                            {
                                new_state[z][y][x][w] = 1;
                            }
                            else 
                            {
                                new_state[z][y][x][w] = 0;
                            }
                        } else
                        {
                            if (occ == 3)
                            {
                                new_state[z][y][x][w] = 1;
                            }
                            else 
                            {
                                new_state[z][y][x][w] = 0;
                            }
                        }
                    }
                }
            }
        }
        four_state = new_state;
    }
   
    int64_t p1 = 0;
    for (int z = 1; z < state.size() - 1; z++)
    {
        for (int y = 1; y < state[z].size() - 1; y++)
        {
            for (int x = 1; x < state[z][y].size() - 1; x++)
            {
                p1 += state[z][y][x];
            }
        }
    }

    int64_t p2 = 0;
    for (int z = 1; z < four_state.size() - 1; z++)
    {
        for (int y = 1; y < four_state[z].size() - 1; y++)
        {
            for (int x = 1; x < four_state[z][y].size() - 1; x++)
            {
                for (int w = 1; w < four_state[z][y][x].size() - 1; w++)
                {
                    p2 += four_state[z][y][x][w];
                }
            }
        }
    }
    std::cout << p1 << "\n";
    std::cout << p2 << "\n";
}  