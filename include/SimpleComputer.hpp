#pragma once

#include <iostream>
#include <csignal>

#include "mem_extern.hpp"
#include "mem_intern.hpp"

#include "user_interaction.hpp"

// !!! Just know this !!!
// All functions of this header are named as sc_<module>.cpp

using namespace std;

namespace myspc
{

class SimpleComputer
{
private:
    internal_memory::Interface internal_mem;
    external_memory::Interface external_mem;
    user_interaction::Interface system_io;

private:
public:
    SimpleComputer();
    bool run_status;
    void Init();
    void Process();
    void End();
};

} // namespace myspc
