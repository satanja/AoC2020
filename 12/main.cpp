#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <utility>
#include <vector>
#include <array>
#include <algorithm>
#include "stefan.h"

int map_char(
    const std::array<char, 7>& index,
    const std::array<char, 7>& map,
    const char c)
{
    auto ptr = std::lower_bound(index.begin(), index.end(), c); // binary search jonges!
    int i = ptr - index.begin();
    return map[i];
}

static int facing = 0;
static int d = 0;
static int x = 0;
static int y = 0;
static int wx = 10;
static int wy = 1;
static int x2 = 0;
static int y2 = 0;
static std::pair<int, int> directions[] = {
        {1, 0},  // E
        {0, -1}, // S
        {-1, 0}, // W
        {0, 1},  // N
};


static std::pair<int, int> rotations[] = {
        {0, 1},  // -270
        {-1, 0}, // -180
        {0, -1}, // -90
        {0, 0},  // 0 dummy
        {0, 1},  // 90
        {-1, 0}, // 180
        {0, -1}  // 270
};

// E
void fn0 ()
{
    x += d;
    wx += d;
}


// S
void fn1 ()
{
    y -= d;
    wy -= d;
}

// W
void fn2 ()
{
    x -= d;
    wx -= d;
}

// N
void fn3 ()
{
    y += d;
    wy += d;
}

// F
void fn4 ()
{
    x += d * directions[facing].first;
    y += d * directions[facing].second;

    x2 += d * wx;
    y2 += d * wy;
}

// L
void fn5 ()
{
    facing = (facing - d / 90);
    if (facing < 0)
    {
        facing += 4;
    }
    int cos = rotations[d / 90 + 3].first;
    int sin = rotations[d / 90 + 3].second;
    int wxt = wx;
    int wyt = wy;
    wx = wxt * cos - wyt * sin;
    wy = wxt * sin + wyt * cos;
}

// R
void fn6 ()
{
    facing = (facing + d / 90);
    if (facing >= 4)
    {
        facing -= 4;
    }

    d *= -1;
    int cos = rotations[d / 90 + 3].first;
    int sin = rotations[d / 90 + 3].second;
    int wxt = wx;
    int wyt = wy;
    wx = wxt * cos - wyt * sin;
    wy = wxt * sin + wyt * cos;
}

void aoc12(const char *arr, int len, unsigned char **out)
{
    std::array<char, 7> index { 'E', 'F', 'L', 'N', 'R', 'S', 'W' };
    std::array<char, 7> map { 0, 4, 5, 3, 6, 1, 2 };

    void (*funcs[])() =
    {
        fn0,
        fn1,
        fn2,
        fn3,
        fn4,
        fn5,
        fn6
    };

    for (int i = 0; i < len; i++)
    {
        char c = arr[i];

        c = map_char(index, map, c);
        i++;
        d = 0;

        while (arr[i] != '\n')
        {
            d *= 10;
            d += arr[i] - '0';
            i++;
        }
        funcs[c]();
    }
}