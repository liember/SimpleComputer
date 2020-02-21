#include "registers.hpp"
#include <iostream>

int Registers::Get(int regist, int *value)
{
    int flag = (flag >> (regist - 1)) & 0x1;
    *value = flag;
    return 0;
}