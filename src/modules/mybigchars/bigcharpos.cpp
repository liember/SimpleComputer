#include "myBigChars.hpp"

int myBigChars::GetBigCharPos(int *big, int x, int y, int *value)
{
    int pos;

    if ((x < 0) || (y < 0) || (x > 7) || (y > 7))
        return -1;
    if (y <= 3)
        pos = 0;
    else
        pos = 1;
    y = y % 4;
    *value = (big[pos] >> (y * 8 + x)) & 1;

    return 0;
}

int myBigChars::SetBigCharPos(int *big, int x, int y, int value)
{
    int pos;

    if ((x < 0) || (y < 0) || (x > 7) || (y > 7) || (value < 0) || (value > 1))
        return -1;
    if (y <= 3)
        pos = 0;
    else
        pos = 1;
    y = y % 4;
    if (value == 0)
        big[pos] &= ~(1 << (y * 8 + x));
    else
        big[pos] |= 1 << (y * 8 + x);

    return 0;
}