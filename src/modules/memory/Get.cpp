#include "memory.hpp"
#include "registers.hpp"
#include <iostream>

int Memory::Get(int adress, int *value)
{
    if (adress >= 100)
    {
        std::cout << "[!] Over the borders." << std::endl;
        Registers::Set(OVER_THE_BORDER, 1);
        return 1;
    }
    *value = mem[adress];
    return 0;
}