#pragma once

#include <cstdint>

#define MEM_SIZE 100 //memory size of your simple computer

#define TOO_FULL 0x01
#define ZERO_DIVIDE 0x02
#define OVER_THE_BORDER 0x03
#define IGNORE 0x04
#define WRONG_COMMAND 0x05

#define FLAG_OVERFLOW 0
#define FLAG_DIVISION 1
#define FLAG_OUTMEM 2
#define FLAG_INTERRUPT 3
#define FLAG_COMMAND 4
#define FLAG_ODD 5

#define ERR_WRONG_ADDR -1
#define ERR_OPEN_FILE -2
#define ERR_FILE_SIZE -3
#define ERR_UNCORRECT_COMMAND -4
#define ERR_ATTRIBUTE_BIT -5
#define ERR_WRONG_FLAG -6

namespace memory
{

class accamulator
{
private:
    uint16_t cell;

public:
    void Set(uint16_t v) { cell = v; }
    uint16_t Get() { return cell; }
};

class Registers
{
private:
    uint8_t flag;

public:
    int Flag() { return flag; }
    int Init();
    int Get(int regist);
    int Set(int regist, int value);
};

class Memory
{
private:
    Registers *rg;

public:
    static int16_t mem[];

public:
    Memory(Registers *r) : rg(r) {}

    int Init();

    int Set(int, int);
    int Get(int, int *);

    int Save(const char *);
    int Load(const char *);

    void Show();
};

} // namespace memory