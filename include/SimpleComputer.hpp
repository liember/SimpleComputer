#pragma once

#include <iostream>
#include <csignal>

#include "interpreter.hpp" // TO DO EXECUTOR INTERFACE

#include "mem_extern.hpp"
#include "mem_intern.hpp"

#include "user_interaction.hpp"

// !!! Just know this !!!
// All functions of this header are named as sc_<module>.cpp

using namespace std;

namespace
{
volatile std::sig_atomic_t gSignalStatus;
}

namespace myspc
{

class SimpleComputer
{
private:
    interpreter interpreter;

    internal_memory::Interface internal_mem;
    external_memory::Interface external_mem;

    user_interaction::Interface system_io; // input output
private:
    void CustomInit();

    // TO DO MOVE THIS INTO EXECUTOR
    // int ALU(int command, int operand);
    // void CU();

    void SigHandle(int sig);

public:
    SimpleComputer();

    bool run_status;

    void Init();

    void DrawUI();
    void Process();

    void End();
};

class InterruptManager
{
private:
    static constexpr int ContinueWorking = 1; // timeout let's go to working!
    static constexpr int ResetSystem = 2;

    static SimpleComputer *ScPc;

public:
    static void SignalHandle(int sig);
    static void Reset(int sig);

    InterruptManager();
};

} // namespace myspc
