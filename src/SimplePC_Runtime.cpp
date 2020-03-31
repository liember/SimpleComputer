#include "SimpleComputer.hpp"

using namespace myspc;

void SimpleComputer::CustomInit()
{
    window->ClrScr();
}

void SimpleComputer::DrawUI()
{
    user_interface->Draw();
}

void SimpleComputer::InputHandle()
{
    window->term->GotoXY(0, 22);
    cout << endl;

    keyboard->ReadKey();
    char *buf = keyboard->GetKey();

    int lastkey = 0;

    if (strcmp(buf, "l") == 0)
        lastkey = l;
    else if (strcmp(buf, "s") == 0)
        lastkey = s;
    else if (strcmp(buf, "r") == 0)
        lastkey = r;
    else if (strcmp(buf, "t") == 0)
        lastkey = t;
    else if (strcmp(buf, "i") == 0)
        lastkey = i;
    else if (strcmp(buf, "q") == 0)
        lastkey = q;
    else if (strcmp(buf, "\n") == 0)
        lastkey = enter;
    else if (strcmp(buf, "\033[15~") == 0)
        lastkey = f5;
    else if (strcmp(buf, "\033[17~") == 0)
        lastkey = f6;
    else if (strcmp(buf, "\033[A") == 0)
        SelectUpper();
    else if (strcmp(buf, "\033[B") == 0)
        SelectLower();
    else if (strcmp(buf, "\033[C") == 0)
        SelectRight();
    else if (strcmp(buf, "\033[D") == 0)
        SelectLeft();
    else
        lastkey = other;
    * /
}

void SimpleComputer::Process()
{
    memory::Memory::mem[0] = 123;
    user_interface->SetSelectedNumber(0);
}