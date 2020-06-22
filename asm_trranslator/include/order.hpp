#pragma once

#include <map>
#include <ctype.h>
#include <iostream>
#include <iomanip>

#include "MyException.hpp"

class order
{
private:
    static int max_mem;
    static std::map<std::string, uint16_t> commands_list;

    int16_t command;
    const int16_t operand;

public:
    const int16_t address;

    static void SetMemorySize(int size);
    int16_t GetBinary();
    order(uint16_t _addr, std::string _cmd, int16_t _opeand);
    ~order();
};