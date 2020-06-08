#include "mem_extern.hpp"

using namespace external_memory;

RandomAcsessMemory::RandomAcsessMemory() : size(standart_memory_size)
{
    memory = new int16_t[standart_memory_size];
}

RandomAcsessMemory::RandomAcsessMemory(int s) : size(s)
{
    memory = new int16_t[size];
}

RandomAcsessMemory::~RandomAcsessMemory()
{
    delete memory;
}

int16_t RandomAcsessMemory::Get(unsigned int index)
{
    if (index >= standart_memory_size)
        return memory[standart_memory_size - 1];
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
    FILE *fp;
    if ((fp = fopen(filename, "rb")) != nullptr)
    {
        fread(memory, sizeof(uint16_t), size, fp);
        fclose(fp);
    }
}

void RandomAcsessMemory::Save(const char *filename)
{
    FILE *fp;
    if ((fp = fopen(filename, "wb")) != nullptr)
    {
        for (int i = 0; i < size; i++)
        {
            fwrite(&memory[i], sizeof(uint16_t), 1, fp);
        }
        fclose(fp);
    }
}

void RandomAcsessMemory::Set(int adress, uint16_t value)
{
    if (adress >= size)
    {
        throw OVER_THE_BORDER;
    }
    memory[adress] = value;
}
