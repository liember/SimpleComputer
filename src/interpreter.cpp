#include "Executor.hpp"
#include <iostream>

using namespace ALU;

int Interpreter::Decode(const uint16_t value, uint8_t *command, uint8_t *operand)
{
    int attribute;
    int tmp_command, tmp_operand;
    attribute = (value >> 14) & 1;
    if (attribute == 0)
    {
        tmp_command = (value >> 7) & 0x7F;
        tmp_operand = value & 0x7F;

        bool command_is_defined = true;
        for (int i = 0; i < check_list_size; i++)
        {
            if (*command == check_list[i])
            {
                command_is_defined = true;
            }
        }
        if (command_is_defined)
        {
            *command = tmp_command;
            *operand = tmp_operand;
        }
        else
        {
            throw errors::undef_comand;
        }
    }
    else
    {
        throw errors::non_comand_data;
    }
    return 0;
}
int Interpreter::Encode(uint8_t command, uint8_t operand, uint16_t *value)
{
    if (operand > 127)
    {
        throw errors::long_operand;
    }

    bool command_is_defined = true;
    for (int i = 0; i < check_list_size; i++)
    {
        if (command == check_list[i])
        {
            command_is_defined = true;
        }
    }
    if (!command_is_defined)
    {
        throw errors::undef_comand;
    }
    *value = 0;
    *value = (command << 7) | operand;
    return 0;
}