#include "SimpleComputer.hpp"

using namespace myspc;

int SimpleComputer::ALU(int command, int operand)
{
    int tmp;

    switch (command)
    {
    case comands::add:
        acc->Set(acc->Get() + memory::Memory::mem[operand]);
        break;

    case comands::sub:
        if (((memory::Memory::mem[operand] >> 14) & 1) == 1)
            tmp = memory::Memory::mem[operand] | (~0x7FFF);
        else
            tmp = memory::Memory::mem[operand];
        acc->Set(acc->Get() - tmp);
        if ((acc->Get() > ((int)(~0x7FFF))) && (acc->Get() <= 0x7FFF))
        {
            acc->Set(acc->Get() & 0x7FFF);
        }
        break;

    case comands::mul:
        acc->Set(acc->Get() * memory::Memory::mem[operand]);
        break;

    case comands::divide:
        if (memory::Memory::mem[operand] != 0)
            acc->Set(acc->Get() / memory::Memory::mem[operand]);
        else
        {
            rg->Set(FLAG_DIVISION, 1);
            return -1;
        }
        break;
    }
    if ((acc->Get() & 1) == 0)
        rg->Set(FLAG_ODD, 0);
    else
        rg->Set(FLAG_ODD, 1);
    if ((acc->Get() > 0x7FFF) || (acc->Get() < 0))
    {
        acc->Set(acc->Get() & 0x7FFF);
        rg->Set(FLAG_OVERFLOW, 1);
    }
    else
        rg->Set(FLAG_OVERFLOW, 0);
    rg->Set(FLAG_ODD, acc->Get() & 1);
    return 0;
}