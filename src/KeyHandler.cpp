#include "user_interaction.hpp"

using namespace user_interaction;

void KeyHandler::Load()
{
    std::cout << "Filename: ";
    std::string name;
    std::cin >> name;
    //sc_mem->Load(name.c_str());
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

uint16_t KeyHandler::GetValue()
{
    std::cout << "Value: ";
    uint16_t val;
    std::cin >> val;
    return val;
}

void KeyHandler::SelectUpper(int &cur)
{
    if (cur / 10 != 0)
    {
        cur -= 10;
    }
}
void KeyHandler::SelectLower(int &cur)
{
    if (cur + 10 < 99)
    {
        cur += 10;
    }
}

void KeyHandler::SelectRight(int &cur)
{
    if (cur % 10 != 9)
    {
        cur++;
    }
}

void KeyHandler::SelectLeft(int &cur)
{
    if (cur % 10 != 0)
    {
        cur--;
    }
}