#include "SimpleComputer.hpp"

using namespace myspc;

void SimpleComputer::CustomInit()
{
    //user_interface.ClearrScreen();
    //user_interface.SetSelectedCell(14);

    internal_mem.registers.Set(FLAG_INTERRUPT, 1);
}

void SimpleComputer::Process()
{
    //TO DO INTERUPT MANAGER
    /*
    if (.Get(FLAG_INTERRUPT))
    {
        InputHandle();
    }
    else
    {
    }
    */
}