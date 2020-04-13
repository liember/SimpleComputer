#pragma once

#include "mem_intern.hpp"
#include "mem_extern.hpp"

namespace ALU
{

enum errors
{
    overflow,
    undef_comand,
    non_comand_data,
    long_operand,
};

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
private:
    int check_list_size = 13;
    static constexpr uint8_t check_list[] = {comands::Read,
                                             comands::Write,
                                             comands::load,
                                             comands::store,
                                             comands::add,
                                             comands::sub,
                                             comands::divide,
                                             comands::mul,
                                             comands::jump,
                                             comands::jneg,
                                             comands::jz,
                                             comands::halt,
                                             comands::And};

public:
    int Encode(uint8_t command, uint8_t operand, int *value);
    int Decode(const int value, uint8_t *command, uint8_t *operand);
};

class Executor
{
public:
    // operand means cell of memory
    int Calculate(const uint8_t command, const uint8_t operand, uint8_t &accum);
    int Commutate(const uint8_t command, const uint8_t operand, const uint8_t accum, uint8_t &counter);
    int Move(const uint8_t command, uint8_t &operand, uint8_t &accum);
    int InputOut(const uint8_t command, uint8_t &operand);
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