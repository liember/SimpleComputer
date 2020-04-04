#include "SimpleComputer.hpp"

using namespace myspc;

void ui::print_flags(int x, int y)
{
    x += 6;
    window->term->GotoXY(x, y);
    if (rg->Flag() & (1 << FLAG_OVERFLOW))
        cout << "O";
    else
        printf(" ");

    window->term->GotoXY(x + 3, y);
    if (rg->Flag() & (1 << FLAG_COMMAND))
        cout << "E";
    else
        printf(" ");

    window->term->GotoXY(x + 6, y);
    if (rg->Flag() & (1 << FLAG_INTERRUPT))
        printf("V");
    else
        printf(" ");

    window->term->GotoXY(x + 9, y);
    if (rg->Flag() & (1 << FLAG_OUTMEM))
        printf("M");
    else
        printf(" ");

    window->term->GotoXY(x + 12, y);
    if (rg->Flag() & (1 << FLAG_DIVISION))
        printf("Z");
    else
        printf(" ");
}

void ui::print_keys(int x, int y)
{
    window->term->GotoXY(x, y);
    printf("l  - load");
    window->term->GotoXY(x, y + 1);
    printf("s  - save");
    window->term->GotoXY(x, y + 2);
    printf("r  - run");
    window->term->GotoXY(x, y + 3);
    printf("t  - step");
    window->term->GotoXY(x, y + 4);
    printf("i  - reset");
    window->term->GotoXY(x, y + 5);
    printf("F5 - accumulator");
    window->term->GotoXY(x, y + 6);
    printf("F6 - instructionCounter");
}

void ui::print_memory(int x, int y)
{
    int i, j;
    int smem, command;

    for (i = 0; i < 10; i++)
    {
        window->term->GotoXY(x, y + i);
        for (j = 0; j < 9; j++)
        {
            smem = memory::Memory::mem[i * 10 + j] & 0x3FF;
            command = (memory::Memory::mem[i * 10 + j] >> 14) & 1;
            if (command == 0)
            {
                window->term->SetBgColor(terminal::myTerm::colors::brown);
                std::cout << "+";
            }
            else
            {
                window->term->SetBgColor(terminal::myTerm::colors::magenta);
                std::cout << " ";
            }

            if (i * 10 + j == selected_number)
            {
                window->term->SetBgColor(terminal::myTerm::colors::green);
            }
            else if (i * 10 + j == current_operation)
            {
                window->term->SetBgColor(terminal::myTerm::colors::red);
            }
            printf("%0*X ", 4, smem);
        }
        smem = memory::Memory::mem[i * 10 + j] & 0x3FF;
        command = (memory::Memory::mem[i * 10 + j] >> 14) & 1;
        if (command == 0)
            printf("+");
        else
            printf(" ");
        printf("%0*X", 4, smem);
    }
    window->term->SetBgColor(terminal::myTerm::colors::defaul);
}

ui::ui(terminal::VOS *win, memory::Memory *m, memory::Registers *r, memory::accamulator *a)
{
    window = win;
    mem = m;
    rg = r;
    ac = a;
}

int ui::Init()
{
    selected_number = 0;
    box_memory = new gui_kit::titled_box(60, 11, 1, 1, "Memory");
    box_accamulator = new gui_kit::titled_box(25, 2, 62, 1, "Accumulator");
    box_instruction_counter = new gui_kit::titled_box(25, 2, 62, 4, "Instruction Counter");
    box_operation = new gui_kit::titled_box(25, 2, 62, 7, "Operation");
    box_flag = new gui_kit::titled_box(25, 2, 62, 10, "Flags");

    number_selector = new gui_kit::untitled_box(45, 9, 1, 13);
    bh_selected_number = new gui_kit::big_hex_bumbers(12341, 2, 14);

    box_help = new gui_kit::untitled_box(39, 9, 48, 13);

    return 0;
}

int ui::Draw()
{
    box_memory->Draw();
    print_memory(2, 2);

    box_accamulator->Draw();
    window->term->GotoXY(72, 2);
    printf("%0*X ", 4, ac->Get());

    box_instruction_counter->Draw();

    box_operation->Draw();
    window->term->GotoXY(72, 8);
    printf("%0*X ", 4, memory::Memory::mem[current_operation]);

    box_flag->Draw();
    print_flags(62, 11);

    number_selector->Draw();
    bh_selected_number->Draw();
    bh_selected_number->SetNumber(memory::Memory::mem[selected_number]);
    // help window
    box_help->Draw();
    print_keys(50, 14);

    window->term->GotoXY(1, 23);
    std::cout << "Input/Output: " << std::endl;
    return 0;
}

void ui::SetSelectedCell(int i)
{
    selected_number = i;
}

int ui::CurrentCell()
{
    return selected_number;
}

void ui::SetSelectedOperation(int i)
{
    current_operation = i;
}