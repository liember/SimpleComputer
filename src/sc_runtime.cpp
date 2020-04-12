#include "SimpleComputer.hpp"

using namespace myspc;

SimpleComputer::SimpleComputer() : internal_mem(),
                                   external_mem(),
                                   system_io(external_mem, internal_mem)
{
}

void SimpleComputer::Init()
{
    run_status = true;
}

void SimpleComputer::End()
{
}

void SimpleComputer::Process()
{
    system_io.DrawInterface();
    system_io.ReadKey();
}