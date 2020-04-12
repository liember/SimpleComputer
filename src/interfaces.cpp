#include "mem_extern.hpp"
#include "mem_intern.hpp"
#include "terminal.hpp"
#include "user_interaction.hpp"
#include "StringSwitch.hpp"

internal_memory::Interface::Interface() : accamulator(), instruction_count(), registers()
{
    registers.Init();
}

void internal_memory::Interface::Init()
{
    registers.Init();
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
    gui.sys_draw.output.term.ClrScreen();
    input_handler.keyboard.ReadKey();

    std::string key(input_handler.keyboard.GetKey());

    ss_switch(key)
    {
        ss_case("l") : input_handler.Load();
        break;
        ss_case("s") : input_handler.Save();
        break;
        ss_case("r") : break;
        ss_case("t") : break;
        ss_case("i") : internal_memory.Init();
        external_memory.Init();
        break;
        ss_case("q") : break;
        ss_case("\033[15~") : internal_memory.accamulator.cell = input_handler.GetValue();
        break;
        ss_case("\033[17~") : internal_memory.instruction_count.cell = input_handler.GetValue();
        break;
        ss_case("\033[A") : input_handler.SelectUpper(selected_memory);
        break;
        ss_case("\033[B") : input_handler.SelectLower(selected_memory);
        break;
        ss_case("\033[C") : input_handler.SelectRight(selected_memory);
        break;
        ss_case("\033[D") : input_handler.SelectLeft(selected_memory);
        break;
    }
    return 0;
}