#pragma once

#include "mem_intern.hpp"
#include "mem_extern.hpp"

namespace ALU
{

namespace errors
{
namespace execution
{
inline constexpr int overflow = 11;
inline constexpr int zero_division = 22;
} // namespace execution

namespace translation
{
inline constexpr int undef_comand = 22;
inline constexpr int non_comand_data = 33;
inline constexpr int long_operand = 44;
} // namespace translation

} // namespace errors

namespace comands
{
// input/output
inline constexpr int Read = 0x10;
inline constexpr int Write = 0x11;
// moving
inline constexpr int load = 0x20;
inline constexpr int store = 0x21;
// match
inline constexpr int add = 0x30;
inline constexpr int sub = 0x31;
inline constexpr int divide = 0x32;
inline constexpr int mul = 0x33;
// controll flow
inline constexpr int jump = 0x40;
inline constexpr int jneg = 0x41;
inline constexpr int jz = 0x42;
inline constexpr int halt = 0x43;
// logic
inline constexpr int And = 0x52;
} // namespace comands

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