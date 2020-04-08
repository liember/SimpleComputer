#include "SimpleComputer.hpp"

using namespace myspc;

/*
int SimpleComputer::ALU(int command, int operand)
{
    int tmp;

    switch (command)
    {
    case comands::add:

        internal_mem.accamulator.Set(internal_mem.accamulator.Get() + external_mem.ram.Get(operand));
        break;

    case comands::sub:
        if (((memory::Memory::mem[operand] >> 14) & 1) == 1)
            tmp = memory::Memory::mem[operand] | (~0x7FFF);
        else
            tmp = memory::Memory::mem[operand];
        internal_mem.accamulator->Set(acc->Get() - tmp);
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
            internal_mem.accamulator.Set(internal_mem.accamulator.Get() / memory::Memory::mem[operand]);
        else
        {
            internal_mem.registers.Set(FLAG_DIVISION, 1);
            return -1;
        }
        break;
    }
    if ((acc->Get() & 1) == 0)
        internal_mem.registers.Set(FLAG_ODD, 0);
    else
        internal_mem.registers.Set(FLAG_ODD, 1);
    if ((acc->Get() > 0x7FFF) || (acc->Get() < 0))
    {
        acc->Set(acc->Get() & 0x7FFF);
        internal_mem.registers.Set(FLAG_OVERFLOW, 1);
    }
    else
        internal_mem.registers.Set(FLAG_OVERFLOW, 0);
    internal_mem.registers.Set(FLAG_ODD, acc->Get() & 1);
    return 0;
}

void SimpleComputer::CU()
{
    int command, operand;
    int flag, read_suc;

    int cmd_interpreted = interpreter.Decode(memory::Memory::mem[inst_counter], &command, &operand);

    if (inst_counter >= memory::MEM_SIZE)
    {
        rg->Set(FLAG_OUTMEM, 1);
        rg->Set(FLAG_INTERRUPT, 1);
    }
    if (cmd_interpreted)
    {
        rg->Set(FLAG_COMMAND, 1);
        rg->Set(FLAG_INTERRUPT, 1);
        return;
    }
    else if ((operand < 0) || (operand >= memory::MEM_SIZE))
    {
        rg->Set(FLAG_COMMAND, 1);
        rg->Set(FLAG_INTERRUPT, 1);
        return;
    }
    else if ((command >= 0x30) && (command <= 0x33))
    {
        if (ALU(command, operand) != 0)
            rg->Set(FLAG_INTERRUPT, 1);
    }
    else
    {
        switch (command)
        {
        case comands::Read:
            // do
            // {
            //     read_suc = read_mcell(operand);  sc_mem->
            // } while (read_suc != 0);
            break;

        case comands::Write:
            // write_used = 1;
            // write_val = sc_memory[operand];
            break;

        case comands::load:
            acc->Set(memory::Memory::mem[operand]);
            break;

        case comands::store:
            memory::Memory::mem[operand] = acc->Get();
            break;

        case comands::jump:
            inst_counter = operand - 1;
            break;

        case comands::jneg:
            if (((acc->Get() >> 14) & 1) == 1)
                inst_counter = operand - 1;
            break;

        case comands::jz:
            if (acc->Get() == 0)
                inst_counter = operand - 1;
            break;

        case comands::halt:
            rg->Set(FLAG_INTERRUPT, 1);
            break;
        }
    }
}

*/