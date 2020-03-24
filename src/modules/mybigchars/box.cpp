#include "myBigChars.hpp"

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