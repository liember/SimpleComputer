#pragma once

#define MEM_SIZE 100 //memory size of your simple computer

#define TOO_FULL 0x01
#define ZERO_DIVIDE 0x02
#define OVER_THE_BORDER 0x03
#define IGNORE 0x04
#define WRONG_COMMAND 0x05

class Memory
{
private:
    int mem_size;

public:
    static int mem[];

public:
    int Init();

    int Set(int, int);
    int Get(int, int *);

    int Save(const char *);
    int Load(const char *);

    void Show();
};