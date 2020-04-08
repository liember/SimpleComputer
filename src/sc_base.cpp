#include "SimpleComputer.hpp"

using namespace myspc;

SimpleComputer::SimpleComputer() : interpreter(),
                                   internal_mem(),
                                   external_mem(),
                                   system_io(external_mem, internal_mem)
{
}

void SimpleComputer::DrawUI()
{
    system_io.DrawInterface();
}

/*
void SimpleComputer::SigHandle(int sig)
{
    switch (sig)
    {
    case 1:
        CU();
        inst_counter++;
        if (!rg.Get(FLAG_INTERRUPT))
            alarm(1);
        break;

    case 2:
        sc_mem.Init();
        current_operation = 0;
        rg.Init();
        rg.Set(FLAG_INTERRUPT, 1);
        inst_counter = 0;
        acc.Set(0);
        break;
    }
}
*/

void SimpleComputer::Init()
{
    run_status = true;
    CustomInit();
}

void SimpleComputer::End()
{
    //gui.ClrScr();
    std::cout << "Start saving configuration of SimpleCopmuter" << std::endl;
}

/*
SimpleComputer *InterruptManager::ScPc = nullptr;

InterruptManager::InterruptManager(SimpleComputer *p)
{
    ScPc = p;
    signal(SIGALRM, SignalHandle);
    signal(SIGUSR1, Reset);
}

void InterruptManager::SignalHandle(int sig)
{
    ScPc->SigHandle(ContinueWorking);
}

void InterruptManager::Reset(int sig)
{
    ScPc->SigHandle(ResetSystem);
}
*/