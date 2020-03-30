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

int *myBigChars::ArrToBig(const char *arr)
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
int myBigChars::PrintBox(int x1, int y1, int x2, int y2)
{
    int tmp;
    int maxx = term->GetScreenSizeX(), maxy = term->GetScreenSizeY();

    if (x1 > x2)
    {
        tmp = x1;
        x1 = x2;
        x2 = tmp;
    }
    if (y1 > y2)
    {
        tmp = y1;
        y1 = y2;
        y2 = tmp;
    }
    if ((x1 < 0) || (y1 < 0) || (x2 > maxx) || (y2 > maxy) || (x2 - x1 < 2) ||
        (y2 - y1 < 2))
        return -1;
    term->GotoXY(x1, y1);
    PrintA(BOXCHAR_TL);
    for (int i = x1 + 1; i < x2; i++)
        PrintA(BOXCHAR_HOR);
    PrintA(BOXCHAR_TR);
    for (int i = y1 + 1; i < y2; i++)
    {
        term->GotoXY(x1, i);
        PrintA(BOXCHAR_VERT);
        term->GotoXY(x2, i);
        PrintA(BOXCHAR_VERT);
    }
    term->GotoXY(x1, y2);
    PrintA(BOXCHAR_BL);
    for (int i = x1 + 1; i < x2; i++)
        PrintA(BOXCHAR_HOR);
    PrintA(BOXCHAR_BR);
    return 0;
}
int myBigChars::PrintBigChar(int *big, int x, int y, enum myTerm::colors fg, enum myTerm::colors bg)
{
    int maxx = term->GetScreenSizeX(), maxy = term->GetScreenSizeY();
    int pos, bit;
    int i, j;
    char row[9];

    if ((x < 0) || (y < 0) || (x + 8 > maxx) || (y + 8 > maxy))
        return -1;
    row[8] = '\0';
    term->SetFgColor(fg);
    term->SetBgColor(bg);
    for (i = 0; i < 8; i++)
    {
        for (j = 0; j < 8; j++)
        {
            pos = i >> 2;
            bit = (big[pos] >> ((i % 4) * 8 + j)) & 1;
            if (bit == 0)
                row[j] = ' ';
            else
                row[j] = BOXCHAR_REC;
        }
        term->GotoXY(x, y + i);
        PrintA(row);
    }
    term->SetFgColor(myTerm::colors::defaul);
    term->SetBgColor(myTerm::colors::defaul);
    return 0;
}
int myBigChars::Read(int fd, int *big, int need_count, int *count)
{
    int n, cnt, err;

    err = read(fd, &n, sizeof(n));
    if (err == -1 || (err != sizeof(n)))
        return -1;
    cnt = read(fd, big, need_count * sizeof(int) * 2);
    if (cnt == -1)
        return -1;
    *count = cnt / (sizeof(int) * 2);

    return 0;
}
int myBigChars::Write(int fd, int *big, int count)
{
    int err;

    err = write(fd, &count, sizeof(count));
    if (err == -1)
        return -1;
    err = write(fd, big, count * (sizeof(int)) * 2);
    if (err == -1)
        return -1;

    return 0;
}