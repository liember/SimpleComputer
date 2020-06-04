#include "Executor.hpp"
#include <iostream>

using namespace ALU;

int Interpreter::Decode(const int16_t value, uint8_t *command, uint8_t *operand)
{
    int attribute;
    int tmp_command, tmp_operand;
    attribute = (value >> 14) & 1;
    if (attribute == 1)
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
            return errors::translation::undef_comand;
        }
    }
    else
    {
        return errors::translation::non_comand_data;
    }
    return 0;
}
int Interpreter::Encode(uint8_t command, uint8_t operand, int16_t *value)
{
    if (operand > 127)
    {
        return errors::translation::long_operand;
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
        return errors::translation::undef_comand;
    }
    *value = 0;
    *value = (command << 7) | operand;
    *value = *value | (uint16_t)0x4000;
    return 0;
}