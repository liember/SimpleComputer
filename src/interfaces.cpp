#include "mem_extern.hpp"
#include "mem_intern.hpp"
#include "terminal.hpp"
#include "user_interaction.hpp"

internal_memory::Interface::Interface() : accamulator(), instruction_count(), registers()
{
    registers.Init();
    accamulator.Set(0);
    instruction_count.Set(0);
}

// ############## external_memory #####################

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
    const external_memory::Interface &external,
    const internal_memory::Interface &internal)
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