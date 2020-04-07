#pragma once

#include "terminal.hpp"
#include "guikit.hpp"

// specific user interface class
class user_interface
{
private:
    terminal::Interface terminal;

    int inst_counter;
    int selected_memory_index;

    int accamulator;
    int registers;

    //ui components
    gui_kit::titled_box box_memory;
    gui_kit::titled_box box_accamulator;
    gui_kit::titled_box box_instruction_counter;
    gui_kit::titled_box box_operation;
    gui_kit::titled_box box_flag;
    gui_kit::untitled_box number_selector;
    gui_kit::big_hex_bumbers bh_selected_number;
    gui_kit::untitled_box box_help;

    // ui drawing
    void print_memory(int x, int y, uint16_t *mem);
    void print_keys(int x, int y);
    void print_flags(int x, int y);

public:
    user_interface();
    int Draw(uint16_t *mem);          // draw boxes and states of spc
    void SetSelectedCell(int i);      // index of cell!!!
    int CurrentCell();                // index of cell!!!
    void SetSelectedOperation(int i); // index of cell!!!
};