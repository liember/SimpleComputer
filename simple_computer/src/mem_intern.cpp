#include "mem_intern.hpp"
#include <iostream>

using namespace internal_memory;

int Registers::Get(uint8_t regist)
{
    if ((regist >= 0) && (regist <= 4))
    {
        return (((flags) >> regist) & 1);
    }
    else
        std::cout << std::endl
                  << std::endl
                  << "Undefined register, check your program pls" << std::endl;
    exit(1);
    return 0;
}

void Registers::Init() { flags = 0; }

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

InstructionCounter::InstructionCounter(int limit) : Accamulator(), lim(limit)
{
}

InstructionCounter::InstructionCounter(int limit, uint16_t val) : Accamulator(), lim(limit)
{
    cell = val;
}

void InstructionCounter::up()
{
    if (cell + 1 < lim)
    {
        cell++;
    }
}