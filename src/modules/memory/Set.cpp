#include "memory.hpp"
#include "registers.hpp"

#include <iostream>

int Memory::Set(int adress, int value)
{
    if (adress >= MEM_SIZE)
    {
        std::cout << "[!] Over the borders." << std::endl;
        Registers::Set(OVER_THE_BORDER, 1);
        return 1;
    }
    mem[adress] = value;
    return 0;
}