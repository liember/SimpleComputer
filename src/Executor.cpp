#include "Executor.hpp"

using namespace ALU;

// TO DO MAKE EXCEPTIONS CHECKING

int Executor::Calculate(const uint8_t command, const uint8_t operand, uint8_t &accum)
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

int Executor::Commutate(const uint8_t command, const uint8_t operand, const uint8_t accum, uint8_t &counter)
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

int Executor::Move(const uint8_t command, uint8_t &operand, uint8_t &accum)
{
    switch (command)
    {
    case comands::load:
        accum = operand;
        break;

    case comands::store:
        operand = accum;
        break;
    }
    return 0;
}

int Executor::InputOut(const uint8_t command, uint8_t &operand)
{
    switch (command)
    {
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
    }
    return 0;
}
