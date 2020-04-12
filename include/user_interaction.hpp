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
    gui_kit::base_parameters sys_draw;

    GraphicalInterface();

    // Print elements thats refers to external/internal memory
    void PrintInfo(int registers, int acc, int inst_count, uint16_t *mem);

    // draw boxes and states of spc,
    //but do not draw elements thats refers to memory
    int Draw();
};

class KeyHandler
{
private:
public:
    myReadkey keyboard;

    // key handling functions
    void Load();
    void Save();

    void Run();
    void Step();
    void Enter();

    uint16_t GetValue();

    void SelectUpper(int &);
    void SelectLower(int &);
    void SelectRight(int &);
    void SelectLeft(int &);
};

class Interface
{
public:
    KeyHandler input_handler;
    GraphicalInterface gui;

    external_memory::Interface &external_memory;
    internal_memory::Interface &internal_memory;

    int &selected_memory = gui.selected_mem;

    Interface(external_memory::Interface &, internal_memory::Interface &);

    void DrawInterface();
    void ClearScreen();

    int ReadKey();
};

} // namespace user_interaction