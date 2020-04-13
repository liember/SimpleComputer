#include "Executor.hpp"

using namespace ALU;

// TO DO MAKE EXCEPTIONS CHECKING

int Executor::Calculate(uint8_t command, uint16_t &operand, uint16_t &accum, uint16_t &counter)
{
    switch (command)
    {
    case comands::add:

        accum += operand;
        break;

    case comands::sub:
        accum -= operand;
        break;

    case comands::mul:
        accum *= operand;
        break;

    case comands::divide:
        accum /= operand;
        break;

    case comands::jump:
        counter = operand;
        break;

    case comands::jneg:
        if (accum < 0)
        {
            counter = operand;
        }
        break;

    case comands::jz:
        if (accum == 0)
        {
            counter = operand;
        }
        break;

    case comands::load:
        accum = operand;
        break;

    case comands::store:
        operand = accum;
        break;

    case comands::Read:
        int val;
        std::cin >> val;
        if (val <= 127)
        {
            operand = val;
        }
        else
        {
            throw overflow;
        }
        break;

    case comands::Write:
        std::cout << operand;
        break;

    case comands::halt:
        break;
    }

    return 0;
}
