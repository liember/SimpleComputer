#include "SimpleComputer.hpp"

void SimpleComputer::Init()
{
    rg = new memory::Registers();
    sc_mem = new memory::Memory(rg);
    window = new terminal::VOS();
    user_interface = new sc_ui(window, sc_mem, rg);
    keyboard = new myReadkey();

    run_status = true;

    gui_kit::base_parameters::SetVOS(window);

    sc_mem->Init();
    user_interface->Init();
}

void SimpleComputer::DrawUI()
{
    user_interface->Draw();
}

void SimpleComputer::InputHandle()
{
    window->term->GotoXY(0, 22);
    cout << endl;

    keyboard->ReadKey();
}

void SimpleComputer::Process()
{
}

void SimpleComputer::Save()
{
}

void sc_ui::print_flags(int x, int y)
{
    window->term->GotoXY(x, y);
    if (rg->Flag() & (1 << FLAG_OVERFLOW))
        cout << "O";
    else
        printf(" ");
    if (rg->Flag() & (1 << FLAG_COMMAND))
        cout << "E";
    else
        printf(" ");
    if (rg->Flag() & (1 << FLAG_INTERRUPT))
        printf("V");
    else
        printf(" ");
    if (rg->Flag() & (1 << FLAG_OUTMEM))
        printf("M");
    else
        printf(" ");
    if (rg->Flag() & (1 << FLAG_DIVISION))
        printf("Z");
    else
        printf(" ");
}

void sc_ui::print_keys(int x, int y)
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

void sc_ui::print_memory(int x, int y)
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
                printf("+");
            else
                printf(" ");
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
}

sc_ui::sc_ui(terminal::VOS *win, memory::Memory *m, memory::Registers *r)
{
    window = win;
    mem = m;
    rg = r;
}

int sc_ui::Init()
{
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

int sc_ui::Draw()
{
    box_memory->Draw();
    print_memory(2, 2);

    box_accamulator->Draw();
    box_instruction_counter->Draw();
    box_operation->Draw();
    box_flag->Draw();

    number_selector->Draw();
    bh_selected_number->Draw();
    // help window
    box_help->Draw();
    print_keys(50, 14);

    return 0;
}

void sc_ui::SetSelectedNumber(int i)
{

    selected_number = i;
}
