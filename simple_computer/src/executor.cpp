#include "execution.hpp"

using namespace ALM;

int Executor::Tik(Memory::RandomAcsessMemory &data, Memory::RandomAcsessMemory &commands)
{
    if (!state.Read(Flags::interrupt))
    {
        auto value = commands.Read(instruction_counter.Read());
        try
        {
            Decode(value);
            Calculate(data);
        }
        catch (const std::exception &e)
        {
            state.Set(Flags::interrupt, true);
            std::cerr << e.what() << '\n';
        }
    }
    return 0;
}

void Executor::Calculate(Memory::RandomAcsessMemory &data)
{
    int result = INT32_MAX;
    switch (command)
    {
    case comands::add:
        result = accamulator.Read() + data.Read(operand);
        if (result < max_possible_value)
        {
            accamulator.Set(result);
        }
        else
        {
            throw Errors::Overflow(result);
        }
        break;

    case comands::sub:
        result = accamulator.Read() - data.Read(operand);
        if (result > -max_possible_value)
        {
            accamulator.Set(result);
        }
        else
        {
            throw Errors::Overflow(result);
        }
        break;

    case comands::mul:
        result = accamulator.Read() * data.Read(operand);
        if (result < max_possible_value)
        {
            accamulator.Set(result);
        }
        else
        {
            throw Errors::Overflow(result);
        }
        break;

    case comands::divide:
        if (data.Read(operand) != 0)
        {
            result = accamulator.Read() / data.Read(operand);
            accamulator.Set(result);
        }
        else
        {
            throw Errors::ZeroDivizion(accamulator.Read());
        }

        break;

    case comands::jump:
        instruction_counter.Set(operand - 1);
        break;

    case comands::jneg:
        if (accamulator.Read() < 0)
        {
            instruction_counter.Set(operand - 1);
        }
        break;

    case comands::jz:
        if (accamulator.Read() == 0)
        {
            instruction_counter.Set(operand - 1);
        }
        break;

    case comands::load:
        accamulator.Set(data.Read(operand));
        break;

    case comands::store:
        data.Set(operand, accamulator.Read());
        break;

    case comands::And:
        accamulator.Set(accamulator.Read() & data.Read(operand));
        break;

    case comands::Read:
        int val;
        std::cin >> val;
        if (abs(val) <= max_possible_value)
        {
            data.Set(operand, val);
        }
        else
        {
            throw Errors::Overflow(val);
        }
        break;

    case comands::Write:
        output.Set(data.Read(operand));
        break;

    case comands::halt:
        accamulator.Set(0);
        state.Set(Flags::interrupt, true);
        break;
    }
}

void Executor::Decode(const int16_t value)
{
    if (*std::find(check_list.begin(), check_list.end(), command) != comands::Empty)
    {
        command = (value >> 7) & 0x7F;
        operand = value & 0x7F;
    }
    else
    {
        throw Errors::UndefinedCommand(value);
    }
}

int Executor::GetPos()
{
    return instruction_counter.Read();
}

bool Executor::CheckState()
{
    return state.Read(Flags::interrupt);
}

void Executor::Interrupt()
{
    state.Set(Flags::interrupt, true);
}

int Executor::CheckOutput()
{
    return output.Read();
}

void Executor::Restart()
{
    instruction_counter.Set(0);
    accamulator.Set(0);
}
