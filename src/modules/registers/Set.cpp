#include "registers.hpp"
#include <iostream>

int Registers::Set(int regist, int value)
{
    if (value == 1)
        flag = flag | (1 << regist);
    else if (value == 0)
        flag = flag & (~(1 << regist));
    else
    {
        std::cout << "[!] Invalid value." << std::endl;
        return 1;
    }
    return 0;
}