#pragma once

#include "terminal.hpp"
#include "guikit.hpp"

#include "myReadkey.hpp"

#include "mem_extern.hpp"
#include "mem_intern.hpp"

namespace user_interaction
{

class GraphicalInterface
{
private:
    gui_kit::base_parameters sys_draw;

    //ui components
    gui_kit::titled_box box_memory;
    gui_kit::titled_box box_accamulator;
    gui_kit::titled_box box_instruction_counter;
    gui_kit::titled_box box_operation;
    gui_kit::titled_box box_flag;
    gui_kit::untitled_box number_selector;
    gui_kit::big_hex_bumbers bh_selected_number;
    gui_kit::untitled_box box_help;

    // some ui elements drawing
    void print_keys(int x, int y);
    void print_flags(int x, int y, int registers);
    void print_memory(int x, int y, uint16_t *mem, int selected);

public:
    int selected_mem;
    GraphicalInterface();

    // Print elements thats refers to external/internal memory
    void PrintInfo(int registers, int acc, int inst_count, uint16_t *mem);

    // draw boxes and states of spc,
    //but do not draw elements thats refers to memory
    int Draw();
};

class KeyHandler
{

public:
    myReadkey keyboard;

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
};

class Interface
{
public:
    KeyHandler input_handler;
    GraphicalInterface gui;

    const external_memory::Interface &external_memory;
    const internal_memory::Interface &internal_memory;

    Interface(const external_memory::Interface &, const internal_memory::Interface &);

    void DrawInterface();
};

} // namespace user_interaction