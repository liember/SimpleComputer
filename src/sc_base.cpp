#include "SimpleComputer.hpp"

using namespace myspc;

SimpleComputer *SignalHandler::ScPc = nullptr;

SignalHandler::SignalHandler(SimpleComputer *p)
{
    ScPc = p;
    signal(SIGALRM, SignalHandle);
    signal(SIGUSR1, Reset);
}

void SignalHandler::SignalHandle(int sig)
{
    ScPc->SigHandle(ContinueWorking);
}

void SignalHandler::Reset(int sig)
{
    ScPc->SigHandle(ResetSystem);
}

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

void SimpleComputer::Init()
{
    rg = new memory::Registers();
    sc_mem = new memory::Memory(rg);
    acc = new memory::accamulator();

    window = new terminal::VOS();
    user_interface = new ui(window, sc_mem, rg, acc);
    keyboard = new myReadkey();

    run_status = true;
    current_operation = 0;

    gui_kit::base_parameters::SetVOS(&window);

    sc_mem.Init();
    user_interface.Init();

    SignalHandler sh(this);

    CustomInit();
}

void SimpleComputer::End()
{
    window.ClrScr();
    std::cout << "Start saving configuration of SimpleCopmuter" << std::endl;
}
