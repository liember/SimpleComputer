#include "SimpleComputer.hpp"

using namespace myspc;

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

    gui_kit::base_parameters::SetVOS(window);

    sc_mem->Init();
    user_interface->Init();

    CustomInit();
}

void SimpleComputer::End()
{
    window->ClrScr();
    std::cout << "Start saving configuration of SimpleCopmuter" << std::endl;
}