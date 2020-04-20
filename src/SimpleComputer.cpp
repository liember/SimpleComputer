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

    external_mem.ram.memory[1] = (uint16_t)11;

    external_mem.ram.memory[99] = (uint16_t)15;
    external_mem.ram.memory[98] = (uint16_t)11234;

    processor.translateor.Encode(ALU::comands::add, 1, &external_mem.ram.memory[0]);
    internal_mem.registers.Set(internal_memory::flags::interrupt, true);

    system_io.DrawInterface();
}

void SimpleComputer::End()
{
    system_io.ClearScreen();
}

void SimpleComputer::Process()
{
    switch (system_io.ReadKey())
    {
    case user_interaction::states::run_until_end:
        /* code */
        break;

    case user_interaction::states::run_until_next:
        processor.Step();
        break;

    case user_interaction::states::exit:
        run_status = false;
        break;
    }
    system_io.DrawInterface();
}