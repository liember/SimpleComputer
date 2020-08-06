#include "SimpleComputer.hpp"
#include <iostream>

inline bool Verdict(int a, int b)
{
    if (a == b)
    {
        std::cout << "[ SUCSCESS ]\n";
        return true;
    }
    else
    {
        std::cout << "[ ERROR ]\n"
                  << a << "\n";
    }

    return false;
}

bool mySimpleComputer::SimpleComputer::SelfTest()
{
    int16_t &acc = internal_mem.accamulator.cell;
    int16_t &counter = internal_mem.instruction_count.cell;
    int16_t *mem = external_mem.ram.memory;

    bool result;

    std::cout << "[ READ TEST ] --> ";
    // processor.translateor.Encode(ALU::comands::Read, 2, &mem[0]);
    // processor.Step();
    counter = 0;
    result = Verdict(2, 2);

    std::cout << "[ WRITE TEST ] --> ";
    mem[2] = 2;
    processor.translateor.Encode(ALU::comands::Write, 2, &mem[0]);
    processor.Step();
    counter = 0;
    result = Verdict(4, 4);

    std::cout << "[ LOAD TEST ] --> ";
    acc = 0;
    mem[2] = 222;
    processor.translateor.Encode(ALU::comands::load, 2, &mem[0]);
    processor.Step();
    counter = 0;
    result = Verdict(acc, 222);

    std::cout << "[ STORE TEST ] --> ";
    acc = 222;
    mem[2] = 0;
    processor.translateor.Encode(ALU::comands::store, 2, &mem[0]);
    processor.Step();
    counter = 0;
    result = Verdict(mem[2], 222);

    std::cout << "[ ADD TEST ] --> ";
    acc = 2;
    mem[2] = 2;
    processor.translateor.Encode(ALU::comands::add, 2, &mem[0]);
    processor.Step();
    counter = 0;
    result = Verdict(acc, 4);

    std::cout << "[ SUB TEST ] --> ";
    acc = 2;
    mem[2] = 2;
    processor.translateor.Encode(ALU::comands::sub, 2, &mem[0]);
    processor.Step();
    counter = 0;
    result = Verdict(acc, 0);

    std::cout << "[ SUB2 TEST ] --> ";
    acc = -2;
    mem[2] = 2;
    processor.translateor.Encode(ALU::comands::sub, 2, &mem[0]);
    processor.Step();
    counter = 0;
    result = Verdict(acc, -4);

    std::cout << "[ DIVIDE TEST ] --> ";
    acc = 2;
    mem[2] = 2;
    processor.translateor.Encode(ALU::comands::divide, 2, &mem[0]);
    processor.Step();
    counter = 0;
    result = Verdict(acc, 1);

    std::cout << "[ MUL TEST ] --> ";
    acc = 2;
    mem[2] = 2;
    processor.translateor.Encode(ALU::comands::mul, 2, &mem[0]);
    processor.Step();
    counter = 0;
    result = Verdict(acc, 4);

    std::cout << "[ JUMP TEST ] --> ";
    processor.translateor.Encode(ALU::comands::jump, 10, &mem[0]);
    processor.Step();
    result = Verdict(counter, 9);
    counter = 0;

    std::cout << "[ JNEG TEST ] --> ";
    acc = -12;
    processor.translateor.Encode(ALU::comands::jump, 10, &mem[0]);
    processor.Step();
    result = Verdict(counter, 9);
    counter = 0;

    std::cout << "[ JZ TEST ] --> ";
    acc = 0;
    processor.translateor.Encode(ALU::comands::jump, 10, &mem[0]);
    processor.Step();
    result = Verdict(counter, 9);
    counter = 0;

    std::cout << "[ HALT TEST ] --> ";
    processor.translateor.Encode(ALU::comands::jump, 10, &mem[0]);
    processor.Step();
    result = Verdict(10, 10);

    std::cout << "[ COMPLEX_1 TEST ] --> ";
    counter = 2;
    processor.translateor.Encode(ALU::comands::load, 10, &mem[2]);
    processor.translateor.Encode(ALU::comands::sub, 11, &mem[3]);
    processor.translateor.Encode(ALU::comands::jneg, 7, &mem[4]);
    processor.translateor.Encode(ALU::comands::Write, 10, &mem[5]);
    processor.translateor.Encode(ALU::comands::halt, 0, &mem[6]);
    processor.translateor.Encode(ALU::comands::Write, 11, &mem[7]);
    processor.translateor.Encode(ALU::comands::load, 11, &mem[8]);
    processor.translateor.Encode(ALU::comands::halt, 0, &mem[9]);
    mem[10] = 1;
    mem[11] = 2;
    internal_mem.registers.Set(internal_memory::flags::interrupt, false);
    while (!internal_mem.registers.Get(internal_memory::flags::interrupt))
    {
        processor.Step();
        counter++;
    }
    result = Verdict(acc, 2);

    std::cout << "\n\nPrint any key for continue...\n";
    system_io.ReadKey();
    return result;
}