#include "SimpleComputer.hpp"

using namespace mySimpleComputer;

SimpleComputer::SimpleComputer() : data(100), commands(100)
{
    gui_status = false;
    run_status = false;
}

void SimpleComputer::Init(bool gui)
{
    run_status = true;

    data.Init();
    commands.Init();

    if (gui)
    {
        gui_status = true;
    }
}

void SimpleComputer::End()
{
    // TO DO GUI mode end
}

void SimpleComputer::Restart()
{
    core.Restart();
}

void SimpleComputer::Process()
{
    core.Tik(data, commands);
}

void SimpleComputer::Display()
{
    if (gui_status)
    {
        interface.Draw();
    }

    else
    {
        //TO DO cli mode
        std::cout << "CORE INFO\n";
    }
}

bool SimpleComputer::isRun()
{
    return run_status;
}