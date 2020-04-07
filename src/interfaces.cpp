#include "mem_extern.hpp"
#include "mem_intern.hpp"
#include "terminal.hpp"

internal_memory::Interface::Interface()
{
    registers.Init();
    accamulator.Set(0);
    instruction_count.Set(0);
}

external_memory::Interface::Interface() : ram(standart_memory_size)
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