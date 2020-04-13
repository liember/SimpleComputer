#include "SimpleComputer.hpp"

using namespace mySimpleComputer;

SimpleComputer::SimpleComputer() : internal_mem(),
                                   external_mem(),
                                   system_io(external_mem, internal_mem),
                                   processor(external_mem, internal_mem)
{
}

void SimpleComputer::Init()
{
    run_status = true;
    system_io.ClearScreen();
    system_io.DrawInterface();
}

void SimpleComputer::End()
{
    system_io.ClearScreen();
}

void SimpleComputer::Process()
{
    system_io.ReadKey();

    system_io.DrawInterface();
}