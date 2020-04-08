#include "user_interaction.hpp"

using namespace user_interaction;

void KeyHandler::Load()
{
    // std::cout << "Filename: ";
    // std::string name;
    // std::cin >> name;
    // sc_mem->Load(name.c_str());
}

void KeyHandler::Save()
{
    // std::cout << "Filename: ";
    // std::string name;
    // std::cin >> name;
    // sc_mem->Save(name.c_str());
}

void KeyHandler::Run()
{
    //if (rg->Get(FLAG_INTERRUPT))
    //{
    //    rg->Set(FLAG_INTERRUPT, 0);
    //timer_handler(SIGALRM);
    //}
    //else
    //{
    //    alarm(0);
    //    rg->Set(FLAG_INTERRUPT, 1);
    //}
}

void KeyHandler::Step() {}

void KeyHandler::Reset()
{
    // sc_mem->Init();
    // acc->Set(0);
    // current_operation = 0;
}

void KeyHandler::Accamulator()
{
    // std::cout << "Value: ";
    // uint16_t val;
    // std::cin >> val;
    // acc->Set(val);
}

void KeyHandler::InstructionCounter()
{
    // std::cout << "I dont know what is this ;D";
}

void KeyHandler::SelectUpper()
{
    // int cur = user_interface->CurrentCell();

    // if (cur / 10 != 0)
    // {
    //     user_interface->SetSelectedCell(cur - 10);
    // }
}
void KeyHandler::SelectLower()
{
    // int cur = user_interface->CurrentCell();
    // std::cout << cur;
    // if (cur + 10 < 99)
    // {
    //     user_interface->SetSelectedCell(cur + 10);
    // }
}

void KeyHandler::SelectRight()
{
    // int cur = user_interface->CurrentCell();
    // if (cur % 10 != 9)
    // {
    //     user_interface->SetSelectedCell(cur + 1);
    // }
}

void KeyHandler::SelectLeft()
{
    // int cur = user_interface->CurrentCell();
    // if (cur % 10 != 0)
    // {
    //     user_interface->SetSelectedCell(cur - 1);
    // }
}