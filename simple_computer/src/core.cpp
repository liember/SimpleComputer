#include "core.hpp"

using namespace ALM;

int Executor::Tik(Memory::RandomAcsessMemory &data, Memory::RandomAcsessMemory &commands)
{
    if (!state.Read(Flags::interrupt))
    {
        auto value = commands.Read(instruction_counter.Read());
        try
        {
            Decode(value);
        }
        catch (Errors::UndefinedCommand &e)
        {
            err_msg = "Undef cmd: " + std::to_string(e.GetVal()) + '\n';
        }

        // TO DO fully err log (vall addr, oerands, instruction counter)
        try
        {
            Calculate(data);
        }
        catch (const Memory::Errors::UndefIndex &e)
        {
            state.Set(Flags::error, true);
            err_msg = "Misstake query RAM index: " + std::to_string(e.GetVal()) + '\n';
        }
        catch (const Errors::Overflow &e)
        {
            state.Set(Flags::error, true);
            err_msg = "Calculation value overflow: " + std::to_string(e.GetVal()) + '\n';
        }
        catch (const Errors::ZeroDivizion &e)
        {
            state.Set(Flags::error, true);
            err_msg = "Calculation error (zero division): " + std::to_string(e.GetVal()) + '\n';
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
        if (std::abs(result) < max_possible_value)
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
        if (std::abs(result) < max_possible_value)
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
        if (std::abs(result) < max_possible_value)
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

void Executor::Interrupt()
{
    state.Set(Flags::interrupt, true);
}

void Executor::Restart()
{
    instruction_counter.Set(0);
    accamulator.Set(0);
}

std::string const Executor::GetErr()
{
    return err_msg;
}
