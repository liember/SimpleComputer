#include "registers.hpp"
#include <iostream>
#include "memory.hpp"

int Memory::Get(int adress, int *value)
{
    if (adress >= 100)
    {
        std::cout << "[!] Over the borders." << std::endl;
        Registers::Set(OVER_THE_BORDER, 1);
        return 1;
    }
    *value = mem[adress];
    return 0;
}
int Memory::Init()
{
    for (int i = 0; i < MEM_SIZE; i++)
    {
        mem[i] = 0;
    }
    return 0;
}
int Memory::Load(const char *filename)
{
    FILE *fp;
    if ((fp = fopen(filename, "rb")) == NULL)
    {
        std::cout << "[!] Cannot open file." << std::endl;
        return 1;
    }
    fread(mem, sizeof(int), 100, fp);
    return 0;
}
int Memory::mem[MEM_SIZE];

int Memory::Save(const char *filename)
{
    std::cout << "[?] Saveing data into " << filename << std::endl;
    FILE *fp;
    if ((fp = fopen(filename, "wb")) == NULL)
    {
        std::cout << "[!] Cannot open file." << std::endl;
        return 1;
    }
    for (int i = 0; i < 100; i++)
    {
        fwrite(&mem[i], sizeof(int), 1, fp);
    }
    fclose(fp);
    return 0;
}
int Memory::Set(int adress, int value)
{
    if (adress >= MEM_SIZE)
    {
        std::cout << "[!] Over the borders." << std::endl;
        Registers::Set(OVER_THE_BORDER, 1);
        return 1;
    }
    mem[adress] = value;
    return 0;
}
void Memory::Show()
{
    std::cout << "[?] Memory state at this moment" << std::endl;
    int counter = 0;
    for (int i = 0; i < MEM_SIZE; i++)
    {
        if (counter < 10)
        {
            std::cout << mem[i] << " ";
            counter++;
        }
        else
        {
            std::cout << std::endl
                      << mem[i] << " ";
            counter = 1;
        }
    }
    std::cout << std::endl;
}