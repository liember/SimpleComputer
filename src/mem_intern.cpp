#include "mem_intern.hpp"
#include <iostream>

using namespace internal_memory;

bool Registers::Get(uint8_t regist)
{
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
    if (value)
        flags = flags | (1 << regist);
    else
        flags = flags & (~(1 << regist));
}

void Accamulator::Set(int16_t v) { cell = v; }
int16_t Accamulator::Get() { return cell; }
Accamulator::Accamulator() : cell(0) {}