#include "memory.hpp"
#include <iostream>

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