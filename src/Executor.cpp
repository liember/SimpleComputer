#include "Executor.hpp"

using namespace ALU;

int Executor::Calculate(const uint16_t command, const uint16_t operand, uint16_t &accum)
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
    }
    return 0;
}

int Commutate(const uint16_t command, const uint16_t operand, const uint16_t accum, uint16_t &counter)
{
    switch (command)
    {
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

    case comands::halt:
        break;
    }
    return 0;
}

int Move(const uint16_t command, const uint16_t &operand, uint16_t &accum)
{
}

int InputOut(const uint16_t command, const uint16_t &operand)
{
}
