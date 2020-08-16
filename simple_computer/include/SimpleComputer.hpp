#pragma once

#include "memory.hpp"
#include "core.hpp"

namespace mySimpleComputer
{

    class SimpleComputer
    {
    private:
        Memory::RandomAcsessMemory data;
        Memory::RandomAcsessMemory commands;

        ALM::Executor core;

        bool run_status;
        bool gui_status;

    public:
        SimpleComputer();

        bool SelfTest();

        bool isRun();
        void Init(bool gui);
        void Process();
        void Display();
        void Restart();
        void End();
    };

} // namespace mySimpleComputer
