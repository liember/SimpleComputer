#pragma once

#include <iostream>

#define MEM_SIZE 100 //memory size of your simple computer

#define TOO_FULL 0x01
#define ZERO_DIVIDE 0x02
#define OVER_THE_BORDER 0x03
#define IGNORE 0x04
#define WRONG_COMMAND 0x05

class Memory
{
private:
    size_t mem_size;

public:
    static int mem[];
    static int flag_reg;

public:
    int Init();

    int Set(int, int);
    int Get(int, int *);

    int Save(const char *);
    int Load(const char *);

    int RegInt(void);
    int RegSet(int, int);
    int RegGet(int, int *);

    void Show();
};