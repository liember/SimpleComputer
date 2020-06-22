#include "order.hpp"

int order::max_mem = 100;

std::map<std::string, uint16_t> order::commands_list = {
    {"READ", 0x10},
    {"WRITE", 0x11},
    {"LOAD", 0x20},
    {"STORE", 0x21},
    {"ADD", 0x30},
    {"SUB", 0x31},
    {"DIVIDE", 0x32},
    {"MUL", 0x33},
    {"JUMP", 0x40},
    {"JNEG", 0x41},
    {"JZ", 0x42},
    {"HALT", 0x43},
    {"AND", 0x52},
    {"=", 0x123}};

order::order(uint16_t _addr, std::string _cmd, int16_t _opeand) : operand(_opeand), address(_addr)
{
    if (commands_list.find(_cmd) == commands_list.end())
    {
        throw Except("Undefined command");
    }

    if (_addr >= max_mem)
    {
        throw Except("Address over of the memory limit");
    }

    if (command != 0x123 && _opeand >= max_mem)
    {
        throw Except("Operand over of the memory limit");
    }
    else
    {
        if (operand > std::abs(0x3fff))
        {
            throw Except("Value overflows");
        }
    }

    command = commands_list[_cmd];

    std::cout << "Registered order: "
              << "[ addr:" << address << " ] [ "
              << _cmd << "/" << command << " ] [ op: "
              << operand << " ]" << std::endl;
}

order::~order()
{
}

int16_t order::GetBinary()
{
    static int callCounter = 0;
    callCounter++;

    if (command != 0x123)
    {
        int16_t value = 0;
        value = (command << 7) | operand;
        value = value | (int16_t)0x4000;

        std::cout << std::hex << std::setfill('0') << std::setw(2) << ((value & 0x3fff) >> 7) << std::dec << " calls: " << callCounter << "\n";

        return value;
    }
    return operand;
}

void order::SetMemorySize(int size)
{
    max_mem = size;
}