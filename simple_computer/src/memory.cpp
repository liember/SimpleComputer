#include "memory.hpp"
#include "exceptions.hpp"

#include <iostream>

using namespace Memory;

RandomAcsessMemory::RandomAcsessMemory() : size(standart_memory_size)
{
    if (standart_memory_size > max_mem_size)
    {
        err_info++;
        throw StringException("Standart memory size more than max memory size");
    }

    std::unique_ptr<int16_t[]> new_memory(new int16_t[size]);
    memory.swap(new_memory);
}

RandomAcsessMemory::RandomAcsessMemory(int s) : size(s)
{
    if (s > max_mem_size)
    {
        err_info++;
        throw StringException("Memory size " + std::to_string(s) + " more than max memory size");
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
        throw UndefIndex(index);
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
        throw UndefIndex(index);
    }
    memory[index] = value;
}

int FlagRegisters::Read(uint8_t regist)
{
    if ((regist >= 0) && (regist <= 4))
    {
        return (((flags) >> regist) & 1);
    }
    else
    {
        throw UndefIndex(regist);
    }
    return 0;
}

void FlagRegisters::Init()
{
    flags = 0;
}

void FlagRegisters::Set(uint8_t regist, bool value)
{
    if (value)
        flags = flags | (1 << regist);
    else
        flags = flags & (~(1 << regist));
}

void ValRegister::Set(int16_t v)
{
    cell = v;
}
int16_t ValRegister::Read()
{
    return cell;
}

ValRegister::ValRegister() : cell(0) {}
