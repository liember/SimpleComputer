#include "terminal.hpp"
#include <iostream>

using namespace terminal;

VOS::VOS(/* args */)
{
    term = new myTerm();
    bc = new myBigChars(term);
}

VOS::~VOS()
{
    delete bc;
    delete term;
}

void VOS::ClrScr()
{
    term->ClrScr();
}

void VOS::GoToLastRow()
{
    term->GotoXY(0, term->GetScreenSizeY() + 1);
    std::cout << std::endl;
}

VOS::VOS(myTerm *t, myBigChars *b)
{
    term = t;
    bc = b;
}

void VOS::SetSize(int row, int col)
{
    term->SetScreenSize(row, col);
}