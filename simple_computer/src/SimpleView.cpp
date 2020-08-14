#include <string>
#include <sstream>
#include <iomanip>
#include <iostream>

#include "SimpleView.hpp"

using namespace mySimpleComputer;

View::View() : data(0, 0, 10, 10, "Data"),
               command(11, 0, 21, 10, "Commands"),
               accamulator(25, 2, 63, 7, "Accamulator"),
               state(25, 2, 63, 10, "Flags"),
               instruction(25, 2, 63, 4, "Instruction"),
               output(25, 2, 65, 10, "Out")
{
}

int View::Draw()
{
    terminal::comands::ClrScreen();
    data.Print();
    command.Print();
    accamulator.Print();
    instruction.Print();
    state.Print();
    output.Print();
    return 0;
}
