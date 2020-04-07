#include "mem_intern.hpp"
#include <iostream>

using namespace internal_memory;

bool Registers::Get(uint8_t regist)
{
    if (regist > 5)
        throw UNKONWN_REGISTER;

    int ans = (flags >> (regist - 1)) & 0x1;

    if (ans == 1)
    {
        return true;
    }
    return false;
}

void Registers::Init()
{
    flags = 0;
}

void Registers::Set(uint8_t regist, bool value)
{
    if (regist > 5)
        throw UNKONWN_REGISTER;
    if (value)
        flags = flags | (1 << regist);
    else
        flags = flags & (~(1 << regist));
}