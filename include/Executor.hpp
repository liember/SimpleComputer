#pragma once

#include "mem_intern.hpp"
#include "mem_extern.hpp"

namespace ALU
{

namespace errors
{
enum execution
{
    overflow = 11,
    zero_division = 22,
    endprogram = 33
};

enum translation
{
    undef_comand = 44,
    non_comand_data = 55,
    long_operand = 66
};

} // namespace errors

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
    int Encode(uint8_t command, uint8_t operand, int16_t *value);
    int Decode(const int16_t value, uint8_t *command, uint8_t *operand);
};

class Executor
{
public:
    // operand means cell of memory
    int Calculate(uint8_t command, int16_t &operand, int16_t &accum, int16_t &counter);
};

class Interface
{
public:
    Interpreter translateor;
    Executor maker;

    external_memory::Interface &external_memory;
    internal_memory::Interface &internal_memory;

    Interface(external_memory::Interface &,
              internal_memory::Interface &);

    int Step();
};

} // namespace ALU