#include "memory.hpp"
#include <iostream>

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