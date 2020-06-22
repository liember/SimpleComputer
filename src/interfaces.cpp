#include "mem_extern.hpp"
#include "mem_intern.hpp"

#include "terminal.hpp"

#include "user_interaction.hpp"
#include "StringSwitch.hpp"

#include "Executor.hpp"

internal_memory::Interface::Interface(int memsize) : accamulator(), instruction_count(memsize), registers()
{
    registers.Init();
}

void internal_memory::Interface::Init()
{
    registers.Init();
    registers.Set(internal_memory::flags::interrupt, true);
    accamulator.Set(0);
    instruction_count.Set(0);
}

// ############## external_memory #####################

void external_memory::Interface::Init()
{
    ram.Init();
}

external_memory::Interface::Interface() : ram()
{
    ram.Init();
}

external_memory::Interface::Interface(int ram_size) : ram(ram_size)
{
    ram.Init();
}

// ############## terminal #####################

void terminal::Interface::GoToLastRow()
{
    term.GotoXY(0, term.GetScreenSizeY() + 1);
    std::cout << std::endl;
}

// ############## user_interaction #####################

user_interaction::Interface::Interface(
    external_memory::Interface &external,
    internal_memory::Interface &internal)
    : input_handler(),
      gui(),
      external_memory(external),
      internal_memory(internal) {}

void user_interaction::Interface::DrawInterface()
{
    gui.Draw();
    gui.PrintInfo(internal_memory.registers.flags,
                  internal_memory.accamulator.cell,
                  internal_memory.instruction_count.cell,
                  external_memory.ram.memory);
}

void user_interaction::Interface::ClearScreen()
{
    gui.sys_draw.output.term.ClrScreen();
}

int user_interaction::Interface::ReadKey()
{
    input_handler.keyboard.ReadKey();

    std::string key(input_handler.keyboard.GetKey());
    ss_switch(key)
    {
        ss_case(ar_up_key) : input_handler.SelectUpper(selected_memory);
        break;
        ss_case(ar_do_key) : input_handler.SelectLower(selected_memory);
        break;
        ss_case(ar_ri_key) : input_handler.SelectRight(selected_memory);
        break;
        ss_case(ar_le_key) : input_handler.SelectLeft(selected_memory);
        break;

    default:
        if (internal_memory.registers.Get(internal_memory::flags::interrupt) == 1)
        {
            ss_switch(key)
            {
                ss_case(l_key) : input_handler.Load(external_memory.ram);
                break;
                ss_case(s_key) : input_handler.Save(external_memory.ram);
                break;
                ss_case(r_key) : return states::run_until_end;
                break;
                ss_case(t_key) : return states::run_until_next;
                break;
                ss_case(i_key) : internal_memory.Init();
                external_memory.Init();
                break;
                ss_case(q_key) : return states::exit;
                break;
                ss_case(f5_key) : internal_memory.accamulator.cell = input_handler.GetValue();
                break;
                ss_case(f6_key) : internal_memory.instruction_count.cell = input_handler.GetValue();
                internal_memory.registers.Init();
                internal_memory.registers.Set(internal_memory::flags::interrupt, true);
                break;
            }
        }
        break;
    }

    return 0;
}

//  ############## executeor #####################

ALU::Interface::Interface(external_memory::Interface &external,
                          internal_memory::Interface &internal)
    : translateor(),
      maker(),
      external_memory(external),
      internal_memory(internal)
{
}

int ALU::Interface::Step()
{
    uint8_t comand, operand;
    int16_t value = external_memory.ram.Get(internal_memory.instruction_count.cell);

    if (translateor.Decode(value, &comand, &operand) == 0)
    {
        if (operand < 100)
        {
            int calc_result;
            int16_t &operand_value = external_memory.ram.memory[operand];
            if (comand >= ALU::comands::jump)
            {
                int16_t target = (int16_t)operand;
                calc_result = maker.Calculate(comand,
                                              target,
                                              internal_memory.accamulator.cell,
                                              internal_memory.instruction_count.cell);
            }
            else
            {
                calc_result = maker.Calculate(comand,
                                              operand_value,
                                              internal_memory.accamulator.cell,
                                              internal_memory.instruction_count.cell);
            }

            switch (calc_result)
            {
            case ALU::errors::execution::overflow:
                internal_memory.registers.Set(internal_memory::flags::interrupt, true);
                internal_memory.registers.Set(internal_memory::flags::overflow, true);
                break;

            case ALU::errors::execution::zero_division:
                internal_memory.registers.Set(internal_memory::flags::interrupt, true);
                internal_memory.registers.Set(internal_memory::flags::zero_division, true);
                break;

            case ALU::errors::execution::endprogram:
                internal_memory.registers.Set(internal_memory::flags::interrupt, true);
            default:
                return 0;
                break;
            }
        }
        else
        {
            internal_memory.registers.Set(internal_memory::flags::out_of_mem, true);
            internal_memory.registers.Set(internal_memory::flags::interrupt, true);
        }
    }
    else
    {
        internal_memory.registers.Set(internal_memory::flags::command, true);
        internal_memory.registers.Set(internal_memory::flags::interrupt, true);
    }
    return 1;
}