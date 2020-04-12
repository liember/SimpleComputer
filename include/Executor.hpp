#pragma once

#include "mem_intern.hpp"
#include "mem_extern.hpp"

namespace ALU
{

enum comands
{
    // input/output
    Read = 0x10,
    Write = 0x11,
    // moving
    load = 0x20,
    store = 0x21,
    // match
    add = 0x30,
    sub = 0x31,
    divide = 0x32,
    mul = 0x33,
    // controll flow
    jump = 0x40,
    jneg = 0x41,
    jz = 0x42,
    halt = 0x43,
    // logic
    And = 0x52
};

class Interpreter
{
public:
    int Encode(int command, int operand, int *value);
    int Decode(int value, int *command, int *operand);
};

class Executor
{
public:
    // operand means cell of memory
    int Calculate(const uint16_t command, const uint16_t operand, uint16_t &accum);
    int Commutate(const uint16_t command, const uint16_t operand, const uint16_t accum, uint16_t &counter);
    int Move(const uint16_t command, const uint16_t &operand, uint16_t &accum);
    int InputOut(const uint16_t command, const uint16_t &operand);
};

class Interface
{
public:
    Interpreter translateor;
    Executor maker;

    const external_memory::Interface &external_memory;
    const internal_memory::Interface &internal_memory;

    Interface(const external_memory::Interface &,
              const internal_memory::Interface &);
};

} // namespace ALU