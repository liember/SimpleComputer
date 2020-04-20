#pragma once

#include <cstdint>
#include <exception>

namespace internal_memory
{

namespace flags
{
inline constexpr int overflow = 0;      // переполнение  при  выполнении  операции
inline constexpr int zero_division = 1; // ошибка  деления  на  0
inline constexpr int out_of_mem = 2;    // ошибка выхода за границы памяти
inline constexpr int interrupt = 3;     // игнорирование тактовых импульсов
inline constexpr int command = 4;       // указа-на неверная команда

inline constexpr int unkonwn_register = 3;
} // namespace flags

class Accamulator
{
public:
    int16_t cell;

    Accamulator();

    void Set(int16_t v);
    int16_t Get();
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
