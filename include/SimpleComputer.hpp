#pragma once

#include "memory.hpp"
#include "interpreter.hpp"
#include "guikit.hpp"
#include "myReadkey.hpp"

#include <iostream>

using namespace std;

class sc_ui
{
private:
    terminal::VOS *window;
    memory::Memory *mem;
    memory::Registers *rg;

    int selected_number;

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
    int Init();
    int Draw();

    void SetSelectedNumber(int i);

    sc_ui(terminal::VOS *win, memory::Memory *m, memory::Registers *r);
};

class SimpleComputer
{
private:
    memory::Registers *rg;
    memory::Memory *sc_mem;

    terminal::VOS *window;

    myReadkey *keyboard;

    sc_ui *user_interface;

    bool run_status;

private:
public:
    void Init();
    void DrawUI();
    void InputHandle();
    void Process();

    bool IsRunning() { return run_status; }

    void Save();
};
