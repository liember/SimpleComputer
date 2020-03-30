#include "registers.hpp"
#include <iostream>

int Registers::flag = 0;

int Registers::Get(int regist, int *value)
{
    int flag = (flag >> (regist - 1)) & 0x1;
    *value = flag;
    return 0;
}

int Registers::Init(void)
{
    flag = 0;
    return 0;
}

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