#include "SimpleUI.hpp"

using namespace mySimpleComputer;

View::View() : data(71, 1, 100, 7, "Data Memory"),
               command(71, 8, 100, 14, "Command Memory"),
               CoreInfo(1, 1, 70, 14, "Core"),
               output(51, 15, 100, 17, "Out"),
               input(1, 15, 50, 17, "Input")
{
}

int View::Draw()
{
    terminal::comands::ClrScreen();
    data.Print();
    command.Print();
    CoreInfo.Print();
    output.Print();
    input.Print();

    terminal::comands::GotoXY(2, 16);
    return 0;
}
