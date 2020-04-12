#include "Executor.hpp"
#include <iostream>

using namespace ALU;

int Interpreter::Decode(int value, int *command, int *operand)
{
    int attribute;
    int tmp_command, tmp_operand;
    attribute = (value >> 14) & 1;
    if (attribute == 0)
    {
        tmp_command = (value >> 7) & 0x7F;
        tmp_operand = value & 0x7F;

        // TO DO CHECKING COMAND DEFIFNITIONS
        bool command_is_defined = true;
        // for (int i = 0; i < 12; i++)
        // {
        //     if (command == comands_list[i])
        //     {
        //         command_is_defined = true;
        //     }
        // }
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
int Interpreter::Encode(int command, int operand, int *value)
{
    if (operand > 127)
    {
        std::cout << "[!] very long operand" << std::endl;
        return 2;
    }

    // TO DO CHECKING COMAND DEFIFNITIONS
    bool command_is_defined = true;
    // for (int i = 0; i < 12; i++)
    // {
    //     if (command == comands_list[i])
    //     {
    //         command_is_defined = true;
    //     }
    // }
    if (command_is_defined)
    {
        *value = 0;
        *value = (command << 7) | operand;
        return 0;
    }
    std::cout << "[!] undefined command" << std::endl;
    return 1;
}