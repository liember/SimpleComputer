#include "memory.hpp"
#include <iostream>

void Memory::Show()
{
    std::cout << "[?] Memory state at this moment" << std::endl;
    int counter = 0;
    for (int i = 0; i < MEM_SIZE; i++)
    {
        if (counter < 10)
        {
            std::cout << mem[i] << " ";
            counter++;
        }
        else
        {
            std::cout << std::endl
                      << mem[i] << " ";
            counter = 1;
        }
    }
    std::cout << std::endl;
}