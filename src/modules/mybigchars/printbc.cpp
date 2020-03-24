#include "myBigChars.hpp"

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