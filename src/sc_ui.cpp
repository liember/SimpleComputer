#include "SC_GUI.hpp"
#include "mem_intern.hpp"

user_interface::user_interface() : terminal(), selected_memory_index(0),
                                   box_memory(60, 11, 1, 1, "Memory"),
                                   box_accamulator(25, 2, 62, 1, "Accumulator"),
                                   box_instruction_counter(25, 2, 62, 4, "Instruction Counter"),
                                   box_operation(25, 2, 62, 7, "Operation"), box_flag(25, 2, 62, 10, "Flags"),
                                   number_selector(45, 9, 1, 13),
                                   bh_selected_number(12341, 2, 14),
                                   box_help(39, 9, 48, 13)
{
}

void user_interface::print_flags(int x, int y)
{
    x += 6;
    terminal.term.GotoXY(x, y);
    if (registers & (1 << FLAG_OVERFLOW))
        std::cout << "O";
    else
        printf(" ");

    terminal.term.GotoXY(x + 3, y);
    if (registers & (1 << FLAG_COMMAND))
        std::cout << "E";
    else
        printf(" ");

    terminal.term.GotoXY(x + 6, y);
    if (registers & (1 << FLAG_INTERRUPT))
        printf("V");
    else
        printf(" ");

    terminal.term.GotoXY(x + 9, y);
    if (registers & (1 << FLAG_OUTMEM))
        printf("M");
    else
        printf(" ");

    terminal.term.GotoXY(x + 12, y);
    if (registers & (1 << FLAG_DIVISION))
        printf("Z");
    else
        printf(" ");
}

void user_interface::print_keys(int x, int y)
{
    terminal.term.GotoXY(x, y);
    printf("l  - load");
    terminal.term.GotoXY(x, y + 1);
    printf("s  - save");
    terminal.term.GotoXY(x, y + 2);
    printf("r  - run");
    terminal.term.GotoXY(x, y + 3);
    printf("t  - step");
    terminal.term.GotoXY(x, y + 4);
    printf("i  - reset");
    terminal.term.GotoXY(x, y + 5);
    printf("F5 - accumulator");
    terminal.term.GotoXY(x, y + 6);
    printf("F6 - instructionCounter");
}

void user_interface::print_memory(int x, int y, uint16_t *mem)
{
    int i, j;
    int smem, command;

    for (i = 0; i < 10; i++)
    {
        terminal.term.GotoXY(x, y + i);
        for (j = 0; j < 9; j++)
        {
            smem = mem[i * 10 + j] & 0x3FF;
            command = (mem[i * 10 + j] >> 14) & 1;
            if (command == 0)
            {
                terminal.term.SetBgColor(terminal::colors::brown);
                std::cout << "+";
            }
            else
            {
                terminal.term.SetBgColor(terminal::colors::magenta);
                std::cout << " ";
            }

            if (i * 10 + j == selected_memory_index)
            {
                terminal.term.SetBgColor(terminal::colors::green);
            }
            else if (i * 10 + j == selected_memory_index)
            {
                terminal.term.SetBgColor(terminal::colors::red);
            }
            printf("%0*X ", 4, smem);
        }
        smem = mem[i * 10 + j] & 0x3FF;
        command = (mem[i * 10 + j] >> 14) & 1;
        if (command == 0)
            printf("+");
        else
            printf(" ");
        printf("%0*X", 4, smem);
    }
    terminal.term.SetBgColor(terminal::colors::defaul);
}

int user_interface::Draw(uint16_t *mem)
{
    box_memory.Draw();
    print_memory(2, 2, mem);

    box_accamulator.Draw();
    terminal.term.GotoXY(72, 2);
    printf("%0*X ", 4, accamulator);

    box_instruction_counter.Draw();
    terminal.term.GotoXY(72, 5);
    printf("%0*X ", 4, inst_counter);

    box_operation.Draw();
    terminal.term.GotoXY(72, 8);
    printf("%0*X ", 4, mem[inst_counter]);

    box_flag.Draw();
    print_flags(62, 11);

    number_selector.Draw();
    bh_selected_number.Draw();
    bh_selected_number.SetNumber(mem[selected_memory_index]);
    // help window
    box_help.Draw();
    print_keys(50, 14);

    terminal.term.GotoXY(1, 23);
    std::cout << "Input/Output: " << std::endl;
    return 0;
}

void user_interface::SetSelectedCell(int i)
{
    selected_memory_index = i;
}

int user_interface::CurrentCell()
{
    return selected_memory_index;
}

void user_interface::SetSelectedOperation(int i)
{
    inst_counter = i;
}