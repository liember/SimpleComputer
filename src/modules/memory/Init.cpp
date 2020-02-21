#include "memory.hpp"
#include <iostream>

int Memory::Init()
{
    for (int i = 0; i < MEM_SIZE; i++)
    {
        mem[i] = 0;
    }
    return 0;
}