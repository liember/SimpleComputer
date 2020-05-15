#pragma once

#include "mem_extern.hpp"
#include "mem_intern.hpp"
#include "user_interaction.hpp"
#include "Executor.hpp"

//TO DO INTERRUPT MANAGER

#include <csignal>

namespace mySimpleComputer
{

    class SimpleComputer
    {
    private:
        internal_memory::Interface internal_mem;
        external_memory::Interface external_mem;
        user_interaction::Interface system_io;
        ALU::Interface processor;

    private:
    public:
        SimpleComputer();

        bool run_status;
        void Init();
        void Process();
        void Run(int sig);
        void Reset(int sig);
        void End();
    };

} // namespace mySimpleComputer
