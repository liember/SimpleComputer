#pragma once

#include "memory.hpp"

#include "interpreter.hpp"
#include "guikit.hpp"
#include "myReadkey.hpp"

#include <iostream>
#include <csignal>

// !!! Just know this !!!
// All functions of this header are named as sc_<module>.cpp

using namespace std;

namespace
{
volatile std::sig_atomic_t gSignalStatus;
}

namespace myspc
{

// specific user interface class
class ui
{
private:
    terminal::VOS *window;
    memory::Memory *mem;
    memory::Registers *rg;
    memory::accamulator *ac;

    int selected_number;   // index of selected number!!!!!
    int current_operation; // index of selected number!!!!!

private:
    //ui components
    gui_kit::titled_box *box_memory;

    gui_kit::titled_box *box_accamulator;
    gui_kit::titled_box *box_instruction_counter;
    gui_kit::titled_box *box_operation;
    gui_kit::titled_box *box_flag;

    gui_kit::untitled_box *number_selector;
    gui_kit::big_hex_bumbers *bh_selected_number;

    gui_kit::untitled_box *box_help;

    // ui drawing
    void print_memory(int x, int y);
    void print_keys(int x, int y);
    void print_flags(int x, int y);

public:
    int Init(); // init boxes

    int Draw(); // draw boxes and states of spc

    void SetSelectedCell(int i); // index of cell!!!
    int CurrentCell();           // index of cell!!!

    void
    SetSelectedOperation(int i); // index of cell!!!

    ui(terminal::VOS *win, memory::Memory *m, memory::Registers *r, memory::accamulator *a);
};

class SimpleComputer
{
private:
    interpreter interpreter;

    memory::Registers rg;
    memory::accamulator acc;

    memory::Memory sc_mem;

    terminal::VOS window;

    myReadkey keyboard;

    ui user_interface;

    bool run_status;

    uint16_t current_operation;
    uint16_t inst_counter;

private:
    void CustomInit();

    // key handling functions
    void Load();
    void Save();

    void Run();
    void Step();
    void Reset();
    void Enter();

    void Accamulator();
    void InstructionCounter();

    void SelectUpper();
    void SelectLower();
    void SelectRight();
    void SelectLeft();

    int ALU(int command, int operand);
    void CU();

    void InputHandle();

public:
    void Init();

    void DrawUI();
    void Process();

    void SigHandle(int sig);

    bool IsRunning() { return run_status; }

    void End();
};

class SignalHandler
{
private:
    static constexpr int ContinueWorking = 1; // timeout let's go to working!
    static constexpr int ResetSystem = 2;

    static SimpleComputer *ScPc;

public:
    static void SignalHandle(int sig);
    static void Reset(int sig);

    SignalHandler(SimpleComputer *);
};

} // namespace myspc
