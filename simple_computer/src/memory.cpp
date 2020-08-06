#include "memory.hpp"
#include "exceptions.hpp"

#include <iostream>

using namespace Memory;

RandomAcsessMemory::RandomAcsessMemory() : size(standart_memory_size)
{
    if (standart_memory_size > max_mem_size) {
        throw StringException("Standart memory size more than max memory size");
    }

    std::unique_ptr<int16_t[]> new_memory(new int16_t[size]);
    memory.swap(new_memory);
}

RandomAcsessMemory::RandomAcsessMemory(int s) : size(s)
{
    if (s > max_mem_size) {
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
        throw StringException("Index of read" + std::to_string(index) + " more than memory size");
    return memory[index];
}

void RandomAcsessMemory::Init()
{
    for (int i = 0; i < size; i++)
    {
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
        throw StringException("Index of set " + std::to_string(index) + " more than memory size");
    memory[index] = value;
}

int FlagRegisters::Read(uint8_t regist)
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

void FlagRegisters::Init() {
    flags = 0;
}

void FlagRegisters::Set(uint8_t regist, bool value)
{
    if (value)
        flags = flags | (1 << regist);
    else
        flags = flags & (~(1 << regist));
}


void ValRegister::Set(int16_t v) {
    cell = v;
}
int16_t ValRegister::Read() {
    return cell;
}

ValRegister::ValRegister() : cell(0) {}

