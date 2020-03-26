#include "myBigChars.hpp"

int myBigChars::PrintA(char *str)
{
    printf("\E(0%s\E(B", str);
    return 0;
}

myBigChars::myBigChars(myTerm *t)
{
    term = t;
}

int *myBigChars::ArrToBig(char *arr)
{
    int *big = new int[2];
    int i;
    int x, y;

    for (i = 0; i < 64; i++)
    {
        x = i % 8;
        y = i / 8;
        SetBigCharPos(big, x, y, arr[i]);
    }
    return big;
}