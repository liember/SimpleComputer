#include "interpreter.hpp"
#include <iostream>

int interpreter::Decode(int value, int *command, int *operand)
{
    int attribute;
    int tmp_command, tmp_operand;
    attribute = (value >> 14) & 1;
    if (attribute == 0)
    {
        tmp_command = (value >> 7) & 0x7F;
        tmp_operand = value & 0x7F;
        bool command_is_defined = false;
        for (int i = 0; i < 12; i++)
        {
            if (tmp_command == comands_list[i])
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
            std::cout << "[!] undefined command" << std::endl;
            return 1;
        }
    }
    else
    {
        std::cout << "[!] attribute of non comand data" << std::endl;
        return 1;
    }
    return 0;
}