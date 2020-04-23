#pragma once

#include <cstdint>

namespace internal_memory
{

enum flags
{
    overflow = 0,      // переполнение  при  выполнении  операции
    zero_division = 1, // ошибка  деления  на  0
    out_of_mem = 2,    // ошибка выхода за границы памяти
    interrupt = 3,     // игнорирование тактовых импульсов
    command = 4,       // указа-на неверная команда

    unkonwn_register = 3
};

class Accamulator
{
public:
    int16_t cell;

    Accamulator();

    void Set(int16_t v);
    int16_t Get();
};

class InstructionCounter : public Accamulator
{
private:
    int lim;

public:
    InstructionCounter(int limit);
    InstructionCounter(int limit, uint16_t val);
    void up();
};

class Registers
{

public:
    uint8_t flags;

    void Init();
    int Get(uint8_t regist);
    void Set(uint8_t regist, bool value);
};

class Interface
{
public:
    Accamulator accamulator;
    InstructionCounter instruction_count;
    Registers registers;
    void Init();
    Interface(int memsize);
};

} // namespace internal_memory
