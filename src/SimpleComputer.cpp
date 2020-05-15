#include "SimpleComputer.hpp"

using namespace mySimpleComputer;

SimpleComputer::SimpleComputer() : internal_mem(100),
                                   external_mem(100),
                                   system_io(external_mem, internal_mem),
                                   processor(external_mem, internal_mem)
{
}

void SimpleComputer::Init()
{
    run_status = true;
    system_io.ClearScreen();

    // test block
    external_mem.ram.memory[0] = (uint16_t)2;
    external_mem.ram.memory[1] = (uint16_t)6;
    processor.translateor.Encode(ALU::comands::load, 0, &external_mem.ram.memory[2]);
    processor.translateor.Encode(ALU::comands::mul, 0, &external_mem.ram.memory[3]);
    processor.translateor.Encode(ALU::comands::add, 0, &external_mem.ram.memory[4]);
    processor.translateor.Encode(ALU::comands::add, 1, &external_mem.ram.memory[5]);
    processor.translateor.Encode(ALU::comands::store, 8, &external_mem.ram.memory[6]);
    processor.translateor.Encode(ALU::comands::halt, 0, &external_mem.ram.memory[7]);
    // end test block

    internal_mem.registers.Set(internal_memory::flags::interrupt, true);
    system_io.DrawInterface();
}

void SimpleComputer::End()
{
    system_io.ClearScreen();
}

void SimpleComputer::Run(int sig)
{
    if (internal_mem.registers.Get(internal_memory::flags::interrupt) == false)
    {
        processor.Step();
        system_io.ClearScreen();
        system_io.DrawInterface();
        internal_mem.instruction_count.up();
        system_io.ClearScreen();
        system_io.DrawInterface();
        alarm(1);
    }
}

void SimpleComputer::Reset(int sig)
{
    internal_mem.Init();
    external_mem.Init();
}

void SimpleComputer::Process()
{
    switch (system_io.ReadKey())
    {
    case user_interaction::states::run_until_end:
        if (internal_mem.registers.Get(internal_memory::flags::interrupt) == true)
        {
            internal_mem.registers.Set(internal_memory::flags::interrupt, false);
            alarm(1);
        }
        break;

    case user_interaction::states::run_until_next:
        processor.Step();
        internal_mem.instruction_count.up();
        break;

    case user_interaction::states::exit:
        run_status = false;
        break;
    }
    system_io.ClearScreen();
    system_io.DrawInterface();
}