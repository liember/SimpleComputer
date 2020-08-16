#include "memory.hpp"

#include <iostream>

using namespace Memory;

RandomAcsessMemory::RandomAcsessMemory() : size(standart_memory_size)
{
    if (standart_memory_size > max_mem_size)
    {
        throw errors::SizeFailrule(standart_memory_size);
    }

    std::unique_ptr<int16_t[]> new_memory(new int16_t[size]);
    memory.swap(new_memory);
}

RandomAcsessMemory::RandomAcsessMemory(int s) : size(s)
{
    if (s > max_mem_size)
    {
        throw errors::SizeFailrule(s);
    }

    std::unique_ptr<int16_t[]> new_memory(new int16_t[size]);
    memory.swap(new_memory);
}

RandomAcsessMemory::~RandomAcsessMemory()
{
    memory.reset();
}

int16_t RandomAcsessMemory::Read(unsigned int index)
{
    if (index >= size)
    {
        err_info++;
        throw errors::UndefIndex(index);
    }
    return memory[index];
}

void RandomAcsessMemory::Init()
{
    for (int i = 0; i < size; i++)
    {
        err_info = 0;
        memory[i] = 0;
    }
}

void RandomAcsessMemory::Load(const char *filename)
{
    // TODO make file load memory
}

void RandomAcsessMemory::Save(const char *filename)
{
    // TODO make meory file save
}

void RandomAcsessMemory::Set(int index, uint16_t value)
{
    if (index >= size)
    {
        err_info++;
        throw errors::UndefIndex(index);
    }
    memory[index] = value;
}

int FlagRegisters::Read(uint8_t regist)
{
    if ((regist >= 0) && (regist <= 7))
    {
        return (((flags) >> regist) & 1);
    }
    else
    {
        throw errors::UndefIndex(regist);
    }
    return 0;
}

void FlagRegisters::Init()
{
    modified = true;
    flags = 0;
}

void FlagRegisters::Set(uint8_t regist, bool value)
{
    if ((regist >= 0) && (regist <= 7))
    {
        modified = true;
        if (value)
            flags = flags | (1 << regist);
        else
            flags = flags & (~(1 << regist));
    }
    else
    {
        throw errors::UndefIndex(regist);
    }
}

void ValRegister::Set(int16_t v)
{
    modified = true;
    cell = v;
}
int16_t ValRegister::Read()
{
    return cell;
}

ValRegister::ValRegister() : cell(0) {}
