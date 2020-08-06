#include "user_interaction.hpp"

using namespace user_interaction;

void KeyHandler::Load(external_memory::RandomAcsessMemory &mem)
{
    std::cout << "Filename: ";
    std::string name;
    std::cin >> name;
    mem.Load(name.c_str());
}

void KeyHandler::Save(external_memory::RandomAcsessMemory &mem)
{
    std::cout << "Filename: ";
    std::string name;
    std::cin >> name;
    mem.Save(name.c_str());
}

int16_t KeyHandler::GetValue()
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
    if (cur + 10 < 100)
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