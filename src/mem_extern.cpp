#include "mem_extern.hpp"

using namespace external_memory;

RandomAcsessMemory::RandomAcsessMemory()
{
    memory = new uint16_t[standart_memory_size];
}

RandomAcsessMemory::RandomAcsessMemory(int size)
{
    memory = new uint16_t[size];
}

RandomAcsessMemory::~RandomAcsessMemory()
{
    delete memory;
}

uint16_t RandomAcsessMemory::Get(unsigned int index)
{
    if (index >= 100)
        throw OVER_THE_BORDER;
    return memory[index];
}

void RandomAcsessMemory::Init()
{
    for (int i = 0; i < memory_size; i++)
    {
        memory[i] = 0;
    }
}

void RandomAcsessMemory::Load(const char *filename)
{
    FILE *fp;
    if ((fp = fopen(filename, "rb")) == nullptr)
    {
        throw FILE_FAIL;
    }
    fread(memory, sizeof(int), memory_size, fp);
    fclose(fp);
}

void RandomAcsessMemory::Save(const char *filename)
{
    FILE *fp;
    if ((fp = fopen(filename, "wb")) == nullptr)
    {
        throw FILE_FAIL;
    }
    for (int i = 0; i < memory_size; i++)
    {
        fwrite(&memory[i], sizeof(int), 1, fp);
    }
    fclose(fp);
}

void RandomAcsessMemory::Set(int adress, uint16_t value)
{
    if (adress >= memory_size)
    {
        throw OVER_THE_BORDER;
    }
    memory[adress] = value;
}
