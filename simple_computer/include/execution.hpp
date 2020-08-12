#pragma once

#include "memory.hpp"
#include "commands.hpp"
#include "exceptions.hpp"

#include <algorithm>
#include <exception>

namespace ALM
{
namespace Errors
{

class ZeroDivizion : virtual public std::exception
{
protected:
    int divided;

public:
    explicit ZeroDivizion(int value)
    {
        divided = value;
    }
    virtual ~ZeroDivizion() throw() {}

    int GetVal()
    {
        return divided;
    }
};

class Overflow : virtual public std::exception
{
protected:
    int overlowed_val;

public:
    explicit Overflow(int value)
    {
        overlowed_val = value;
    }
    virtual ~Overflow() throw() {}

    int GetVal()
    {
        return overlowed_val;
    }
};
} // namespace Errors

enum Flags
{
    interrupt = 0,
    out_of_data = 1,
    out_of_cmd = 2,
};

class Executor
{
private:
    static constexpr int max_possible_value = 0x3fff;

    void Decode(const int16_t value);
    void Calculate(Memory::RandomAcsessMemory &data);

    // used for decode resultss
    uint8_t command;
    uint8_t operand;

    Memory::ValRegister instruction_counter;
    Memory::FlagRegisters state;

    // results of operation pools here
    // (it is buf0)
    Memory::ValRegister accamulator;

    // used for midle resuld of calculation
    Memory::ValRegister buf1;
    Memory::ValRegister buf2;
    Memory::ValRegister buf3;
    Memory::ValRegister buf4;
    Memory::ValRegister buf5;
    Memory::ValRegister buf6;

    // buffer for output values
    // (it is buf7)
    Memory::ValRegister output;

public:
    // sets instruction counter
    // void SetPos(int pos);

    // returns current value (copy of class) of instruction counter
    int GetPos();

    // Returns (true) if interrupt
    bool CheckState();

    // Set interrupt flag - true
    void Interrupt();

    // returns value in output buffer
    // if value is apsent returns MAX_INT
    int CheckOutput();

    // sets instruction counter - 0
    void Restart();

    // make one step of execution
    int Tik(Memory::RandomAcsessMemory &data, Memory::RandomAcsessMemory &commands);
};

} // namespace ALM