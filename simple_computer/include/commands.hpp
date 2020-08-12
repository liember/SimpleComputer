#pragma once

#include <array>
#include <ctype.h>

namespace ALM
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
    And = 0x52,

    Empty = 0
};

std::array<uint8_t, 14> check_list = {comands::Read,
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
                                      comands::And,
                                      comands::Empty};

} // namespace ALM