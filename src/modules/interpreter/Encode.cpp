#include "interpreter.hpp"
#include <iostream>

int interpreter::Encode(int command, int operand, int *value)
{
    if (operand > 127)
    {
        std::cout << "[!] very long operand" << std::endl;
        return 2;
    }
    bool command_is_defined = false;
    for (int i = 0; i < 12; i++)
    {
        if (command == comands_list[i])
        {
            command_is_defined = true;
        }
    }
    if (command_is_defined)
    {
        *value = 0;
        *value = (command << 7) | operand;
        return 0;
    }
    std::cout << "[!] undefined command" << std::endl;
    return 1;
}