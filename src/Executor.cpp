#include "Executor.hpp"

using namespace ALU;

int Executor::Calculate(uint8_t command, int16_t &operand, int16_t &accum, int16_t &counter)
{
    switch (command)
    {
    case comands::add:
        if (accum + operand < 0x3fff)
        {
            accum += operand;
        }
        else
        {
            return errors::execution::overflow;
        }
        break;

    case comands::sub:
        if (accum - operand > -0x3fff)
        {
            accum -= operand;
        }
        else
        {
            return errors::execution::overflow;
        }
        break;

    case comands::mul:
        if (accum * operand < 0x3fff)
        {
            accum *= operand;
        }
        else
        {
            return errors::execution::overflow;
        }
        break;

    case comands::divide:
        if (operand != 0)
        {

            accum /= operand;
        }
        else
        {
            return errors::execution::zero_division;
        }

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
        if (val <= 0x3fff)
        {
            operand = val;
        }
        else
        {
            return errors::execution::overflow;
        }
        break;

    case comands::Write:
        std::cout << operand << std::endl;
        break;

    case comands::halt:
        return errors::execution::endprogram;
        break;
    }

    return 0;
}
