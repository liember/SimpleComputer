#include "SimpleComputer.hpp"

using namespace myspc;

void SimpleComputer::CustomInit()
{
    window->ClrScr();
    user_interface->SetSelectedCell(14);

    rg->Set(FLAG_INTERRUPT, 1);
}

void SimpleComputer::DrawUI()
{
    user_interface->Draw();
    window->GoToLastRow();
    std::cout << endl;
}

void SimpleComputer::InputHandle()
{
    window->term->GotoXY(0, 22);
    cout << endl;

    keyboard->ReadKey();
    char *buf = keyboard->GetKey();

    if (strcmp(buf, "l") == 0)
        Load();
    else if (strcmp(buf, "s") == 0)
        Save();
    else if (strcmp(buf, "r") == 0)
        Run();
    else if (strcmp(buf, "t") == 0)
        Step();
    else if (strcmp(buf, "i") == 0)
        Reset();
    else if (strcmp(buf, "\n") == 0)
        Enter();
    else if (strcmp(buf, "\033[15~") == 0)
        Accamulator();
    else if (strcmp(buf, "\033[17~") == 0)
        InstructionCounter();
    else if (strcmp(buf, "\033[A") == 0)
        SelectUpper();
    else if (strcmp(buf, "\033[B") == 0)
        SelectLower();
    else if (strcmp(buf, "\033[C") == 0)
        SelectRight();
    else if (strcmp(buf, "\033[D") == 0)
        SelectLeft();
}

void SimpleComputer::Process()
{
}