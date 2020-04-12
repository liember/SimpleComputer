#pragma once

#include <cstdint>
#include <exception>

#define FLAG_OVERFLOW 0
#define FLAG_DIVISION 1
#define FLAG_OUTMEM 2
#define FLAG_INTERRUPT 3
#define FLAG_COMMAND 4
#define FLAG_ODD 5

#define UNKONWN_REGISTER 3

namespace internal_memory
{

class Accamulator
{
public:
    uint16_t cell;

    Accamulator();

    void Set(uint16_t v);
    uint16_t Get();
};

class Registers
{

public:
    uint8_t flags;

    void Init();
    bool Get(uint8_t regist);
    void Set(uint8_t regist, bool value);
};

class Interface
{
public:
    Accamulator accamulator;
    Accamulator instruction_count;

    Registers registers;

    void Init();

    Interface();
};

} // namespace internal_memory
