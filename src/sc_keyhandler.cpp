#include "SimpleComputer.hpp"

using namespace myspc;

void SimpleComputer::Load()
{
    std::cout << "Filename: ";
    std::string name;
    std::cin >> name;
    sc_mem->Load(name.c_str());
}

void SimpleComputer::Save()
{
    std::cout << "Filename: ";
    std::string name;
    std::cin >> name;
    sc_mem->Save(name.c_str());
}

void SimpleComputer::Run()
{
    if (rg->Get(FLAG_INTERRUPT))
    {
        rg->Set(FLAG_INTERRUPT, 0);
        //timer_handler(SIGALRM);
    }
    else
    {
        alarm(0);
        rg->Set(FLAG_INTERRUPT, 1);
    }
}

void SimpleComputer::Step() {}

void SimpleComputer::Reset()
{
    sc_mem->Init();
    acc->Set(0);
    current_operation = 0;
}

void SimpleComputer::Enter() {}

void SimpleComputer::Accamulator()
{
    std::cout << "Value: ";
    uint16_t val;
    std::cin >> val;
    acc->Set(val);
}

void SimpleComputer::InstructionCounter()
{
    std::cout << "I dont know what is this ;D";
}

void SimpleComputer::SelectUpper()
{
    int cur = user_interface->CurrentCell();

    if (cur / 10 != 0)
    {
        user_interface->SetSelectedCell(cur - 10);
    }
}
void SimpleComputer::SelectLower()
{

    int cur = user_interface->CurrentCell();
    std::cout << cur;
    if (cur + 10 < 99)
    {
        user_interface->SetSelectedCell(cur + 10);
    }
}
void SimpleComputer::SelectRight()
{
    int cur = user_interface->CurrentCell();
    if (cur % 10 != 9)
    {
        user_interface->SetSelectedCell(cur + 1);
    }
}
void SimpleComputer::SelectLeft()
{
    int cur = user_interface->CurrentCell();
    if (cur % 10 != 0)
    {
        user_interface->SetSelectedCell(cur - 1);
    }
}